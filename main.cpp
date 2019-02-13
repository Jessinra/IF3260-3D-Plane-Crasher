#include <assert.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <ctime>
#include <iostream>
#include <utility>
#include "Master.hpp"
#include "MoveableObject.hpp"
#include "Object.hpp"

using namespace std;

#define MAXHEALTH 8
#define explosiontime 20
#define selectedtime 300
#define degreechange 5
#define maxdegree 50
#define mindegree -50
#define WINDOWHEIGHT 700
#define WINDOWWIDTH 1000

/* Aku sedih */
int deg = 0;
int shoot = 0;
bool keepreading;

void *readinput(void *threadid) {
    char c;
    while (keepreading) {
        c = getchar();
        if (c == '\n') {
            shoot++;
        } else if (c == 'd' && deg <= 100) {
            deg += degreechange;
        } else if (c == 'a' && deg >= -100) {
            deg -= degreechange;
        }
        usleep(10000);
    }
    pthread_exit(NULL);
}

/* Aku sedih */

class Runner : public Master {
protected:
    Object pesawat, meriam, peluru, puing1, puing2, puing3;
    Object revpesawat, revpuing1, revpuing2, revpuing3;
    Object ledakan, misil, hati;

public:
    Runner(int h = WINDOWHEIGHT, int w = WINDOWWIDTH) : Master(h, w) {
        revpesawat = Object(0, 0, "Asset/object_plane3d_right.txt");
        pesawat = Object(0, 0, "Asset/object_plane3d_left.txt");
        meriam = Object(0, 0, "Asset/object_gun.txt");
        peluru = Object(0, 0, "Asset/object_star.txt");
        puing1 = Object(0, 0, "Asset/object_plane3d_part_front.txt");
        puing2 = Object(0, 0, "Asset/object_plane3d_part_wing.txt");
        puing3 = Object(0, 0, "Asset/object_plane3d_part_back.txt");
        revpuing1 = Object(0, 0, "Asset/object_plane_part1.txt");
        revpuing1.reverseHorizontal();
        revpuing2 = Object(0, 0, "Asset/object_plane_part2.txt");
        revpuing2.reverseHorizontal();
        revpuing3 = Object(0, 0, "Asset/object_plane_part3.txt");
        revpuing3.reverseHorizontal();
        ledakan = Object(0, 0, "Asset/object_ledakan.txt");
        misil = Object(0, 0, "Asset/object_misil.txt");
        hati = Object(0, 0, "Asset/object_life.txt");
    }

    void start() {
        int sudut_meriam = 0;
        float titik_acuan_x, titik_acuan_y;
        titik_acuan_x = xend / 2.0f;
        titik_acuan_y = yend - 2;

        pesawat.setPos(Point(xend, 0));
        revpesawat.setPos(Point(-revpesawat.getWidth() + 1, 0));
        meriam.setPos(Point((xend - meriam.getWidth()) / 2.0f,
                            yend - meriam.getHeight() - 2));
        peluru.setPos(
                Point((xend - peluru.getWidth()) / 2.0f,
                      yend - meriam.getHeight() - peluru.getHeight() - 2));
        vector<MoveableObject> planes, rplanes;
        vector<MoveableObject> debris;
        vector<MoveableObject> bullets;
        vector<pair<MoveableObject, int>> explosion;
        vector<MoveableObject> missile;
        MoveableObject cannon = meriam;
        planes.emplace_back(-3, 1, 1, pesawat);
        vector<MoveableObject> lifes;
        MoveableObject life = hati;
        life.selfDilate(0, 0, 0.4);
        for(int i=0;i<MAXHEALTH;++i){
            life.setPos(i * (life.getWidth() + 5) + 5, yend - life.getHeight() - 5);
            lifes.push_back(life);
        }
        for (int i = 1;; i = (i + 1) % 800) {
            // draw
            clearWindow();

            drawObject(cannon);
            drawSolidObject(cannon);
            for (MoveableObject &movableObject : lifes) {
                drawObject(movableObject);
                drawSolidObject(movableObject);
            }
            for (MoveableObject &movableObject : planes) {
                drawObject(movableObject);
                drawSolidObject(movableObject);
            }
            for (MoveableObject &movableObject : rplanes) {
                drawObject(movableObject);
                drawSolidObject(movableObject);
            }
            for (MoveableObject &movableObject : debris) {
                drawObject(movableObject);
                drawSolidObject(movableObject);
            }
            for (MoveableObject &movableObject : bullets) {
                drawObject(movableObject);
                drawSolidObject(movableObject);
            }
            for (pair<MoveableObject, int> &movableObject : explosion) {
                float middleX_explosion = movableObject.first.getWidth() / 2.0f;
                float middleY_explosion = movableObject.first.getHeight() / 2.0f;
                movableObject.first.selfDilate(middleX_explosion, middleY_explosion, 1.05);
                drawObject(movableObject.first);
                drawSolidObject(movableObject.first);
                movableObject.second--;
            }
            for (MoveableObject &movableObject : missile) {
                drawObject(movableObject);
                drawSolidObject(movableObject);
            }

            // move and rotate :/
            if (deg != 0) {
                if (deg > 0) {
                    if (sudut_meriam <= maxdegree) {
                        sudut_meriam += degreechange;
                        cannon = MoveableObject(meriam);
                        cannon.selfRotate(titik_acuan_x, titik_acuan_y,
                                          sudut_meriam);
                        deg -= degreechange;
                    } else {
                        deg = 0;
                    }
                } else {
                    if (sudut_meriam >= mindegree) {
                        sudut_meriam -= degreechange;
                        cannon = MoveableObject(meriam);
                        cannon.selfRotate(titik_acuan_x, titik_acuan_y,
                                          sudut_meriam);
                        deg += degreechange;
                    } else {
                        deg = 0;
                    }
                }
            }
            explosion.erase(remove_if(explosion.begin(), explosion.end(), [](const pair<MoveableObject, int> &a) {
                                return a.second <= 0;
                            }),
                            explosion.end());

            vector<char> checkr(rplanes.size(), 1);
            vector<char> checkp(planes.size(), 1);
            vector<char> checkd(debris.size(), 1);
            vector<char> checkm(missile.size(), 1);
            vector<MoveableObject> tmpr; // rplane
            vector<MoveableObject> tmpp; // plane
            vector<MoveableObject> tmpb; // bullet
            vector<MoveableObject> tmpd; // debris
            vector<MoveableObject> tmpm; // missile
            for (int i=0;i<planes.size();++i) {
                planes[i].move();
                if(planes[i].outOfWindow(WINDOWHEIGHT, WINDOWWIDTH)){
                    checkp[i] = 0;
                }
            }
            for (int i=0;i<rplanes.size();++i) {
                rplanes[i].move();
                if(rplanes[i].outOfWindow(WINDOWHEIGHT, WINDOWWIDTH)){
                    checkr[i] = 0;
                }
            }
            for (int j = 0; j < debris.size(); ++j) {
                debris[j].move();
                if (debris[j].outOfWindow(yend, xend)) {
                    checkd[j] = 0;
                }
            }
            for (MoveableObject &bullet : bullets) {
                bullet.move();
            }
            for (int j = 0; j < missile.size(); ++j) {
                missile[j].move();
                if (missile[j].outOfWindow(yend, xend)) {
                    checkm[j] = 0;
                    if (missile[j].getRefPos().getY() >= yend) {
                        if(!lifes.empty()){
                            lifes.pop_back();
                        }
                    }
                }
            }

            // very slow shit
            for (const MoveableObject &objb : bullets) {
                bool bisa = true;
                for (int j = 0; j < planes.size(); ++j) {
                    if (overlap(planes[j], objb)) {
                        // isi pecahan
                        // if (checkp[j]){
                        MoveableObject sp = ledakan;
                        sp.setPos(Point(planes[j].getRefPos().getX() + 100,
                                        planes[j].getRefPos().getY()));
                        explosion.emplace_back(sp, explosiontime);
                        sp = puing2;
                        sp.setPos(Point(planes[j].getRefPos().getX() + 50,
                                        planes[j].getRefPos().getY() + 75));
                        sp.setVector((planes[j].getDx() < 0 ? -1 : 1) *
                                     sin(45 * PI / 180),
                                     cos(45 * PI / 180));
                        sp.setSpeed(2);
                        tmpd.push_back(sp);
                        sp = puing1;
                        sp.setPos(Point(planes[j].getRefPos().getX(),
                                        planes[j].getRefPos().getY() + 25));
                        sp.setVector((planes[j].getDx() < 0 ? -1 : 1) *
                                     sin(60 * PI / 180),
                                     cos(60 * PI / 180));
                        sp.setSpeed(2);
                        tmpd.push_back(sp);
                        sp = puing3;
                        sp.setPos(Point(planes[j].getRefPos().getX() + 50,
                                        planes[j].getRefPos().getY()));
                        sp.setVector((planes[j].getDx() < 0 ? -1 : 1) *
                                     sin(30 * PI / 180),
                                     cos(30 * PI / 180));
                        sp.setSpeed(2);
                        tmpd.push_back(sp);
                        checkp[j] = 0;
                        // }
                        bisa = false;
                    }
                }
                for (int j = 0; j < rplanes.size(); ++j) {
                    if (overlap(rplanes[j], objb)) {
                        // isi pecahan
                        // if (checkp[j]){
                        MoveableObject sp = ledakan;
                        sp.setPos(Point(rplanes[j].getRefPos().getX() + 100,
                                        rplanes[j].getRefPos().getY()));
                        explosion.emplace_back(sp, explosiontime);
                        sp = revpuing1;
                        sp.setPos(Point(rplanes[j].getRefPos().getX() + 150,
                                        rplanes[j].getRefPos().getY()));
                        sp.setVector((rplanes[j].getDx() < 0 ? -1 : 1) *
                                     sin(60 * PI / 180),
                                     cos(60 * PI / 180));
                        sp.setSpeed(2);
                        tmpd.push_back(sp);
                        sp = revpuing2;
                        sp.setPos(Point(rplanes[j].getRefPos().getX() + 100,
                                        rplanes[j].getRefPos().getY() + 50));
                        sp.setVector((rplanes[j].getDx() < 0 ? -1 : 1) *
                                     sin(45 * PI / 180),
                                     cos(45 * PI / 180));
                        sp.setSpeed(2);
                        tmpd.push_back(sp);
                        sp = revpuing3;
                        sp.setPos(Point(rplanes[j].getRefPos().getX(),
                                        rplanes[j].getRefPos().getY()));
                        sp.setVector((rplanes[j].getDx() < 0 ? -1 : 1) *
                                     sin(30 * PI / 180),
                                     cos(30 * PI / 180));
                        sp.setSpeed(2);
                        tmpd.push_back(sp);
                        checkr[j] = 0;
                        // }
                        bisa = false;
                    }
                }
                for (int j = 0; j < debris.size(); ++j) {
                    if (overlap(debris[j], objb)) {
                        checkd[j] = 0;
                        bisa = false;
                    }
                }
                for (int j = 0; j < missile.size(); ++j) {
                    if (overlap(missile[j], objb)) {
                        checkm[j] = 0;
                        bisa = false;
                    }
                }
                if (bisa && !objb.outOfWindow(yend, xend)) {
                    tmpb.push_back(objb);
                }
            }
            for (int j = 0; j < planes.size(); ++j) {
                if (checkp[j])
                    tmpp.push_back(planes[j]);
            }
            for (int j = 0; j < rplanes.size(); ++j) {
                if (checkr[j])
                    tmpr.push_back(rplanes[j]);
            }
            for (int j = 0; j < debris.size(); ++j) {
                if (checkd[j])
                    tmpd.push_back(debris[j]);
            }
            for (int j = 0; j < missile.size(); ++j) {
                if (checkm[j]) {
                    tmpm.push_back(missile[j]);
                }
            }
            rplanes = tmpr;
            planes = tmpp;
            bullets = tmpb;
            debris = tmpd;
            missile = tmpm;

            /* Spawn Section */
            if (shoot > 0) {
                MoveableObject tmp = MoveableObject(peluru);
                tmp.setSpeed(2);
                tmp.selfRotate(titik_acuan_x, titik_acuan_y, sudut_meriam);
                tmp.setVector(sin(sudut_meriam * PI / 180),
                              -cos(sudut_meriam * PI / 180));
                bullets.push_back(tmp);
                shoot--;
            }
            if (i == 0) {
                planes.push_back(MoveableObject(-3, 1, 1, pesawat));
            }
            else if(i == 400){
                rplanes.push_back(MoveableObject(3, 1, 1, revpesawat));
            }
            for (const MoveableObject &obj : planes) {
                if (rand() % selectedtime == 0) {
                    MoveableObject tmp = MoveableObject(0, 1, 1, misil);
                    tmp.setPos(obj.getRefPos().getX() + (obj.getWidth() - tmp.getWidth()) / 2.0f, obj.getRefPos().getY() + 80);
                    missile.push_back(tmp);
                }
            }
            for (const MoveableObject &obj : rplanes) {
                if (rand() % selectedtime == 0) {
                    MoveableObject tmp = MoveableObject(0, 1, 1, misil);
                    tmp.setPos(obj.getRefPos().getX() + (obj.getWidth() - tmp.getWidth()) / 2.0f, obj.getRefPos().getY() + 80);
                    missile.push_back(tmp);
                }
            }

            if (lifes.empty()) {
                break;
            }

            flush();
            usleep(5000);
        }
        puts("GAME OVER!! YOU LOSE");
    }

    bool overlap(const Object &p, const Object &q) {
        int a, b, c, d, e, f, g, h;
        a = p.getRefPos().getX();
        b = p.getRefPos().getY();
        c = a + p.getLowerRight().getX();
        d = b + p.getLowerRight().getY();
        e = q.getRefPos().getX();
        f = q.getRefPos().getY();
        g = e + q.getLowerRight().getX();
        h = f + q.getLowerRight().getY();
        if (a > g || e > c)
            return false;
        if (b > h || f > d)
            return false;
        return true;
    }
};

int main() {
    srand(time(NULL));

    /* non-newline input */
    struct termios org_opts, new_opts;
    int res = 0;
    res = tcgetattr(STDIN_FILENO, &org_opts);
    assert(res == 0);
    memcpy(&new_opts, &org_opts, sizeof(new_opts));
    new_opts.c_lflag &=
            ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | ECHOPRT | ECHOKE | ICRNL);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_opts);

    /* Multithreading part */
    pthread_t thread;
    int rc, id = 0;
    keepreading = true;
    rc = pthread_create(&thread, NULL, readinput, (void *) id);

    Runner run;
    run.start();
    keepreading = false;

    /* close */
    pthread_exit(NULL);
    res = tcsetattr(STDIN_FILENO, TCSANOW, &org_opts);
    assert(res == 0);
    return 0;
}