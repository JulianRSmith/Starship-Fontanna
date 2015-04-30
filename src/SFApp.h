#ifndef SFAPP_H
#define SFAPP_H

#include <memory>   // Pull in std::shared_ptr
#include <iostream> // Pull in std::cerr, std::endl
#include <list>     // Pull in list
#include <sstream>

using namespace std;

#include "SFCommon.h"
#include "SFEvent.h"
#include "SFAsset.h"

/**
 * Represents the StarshipFontana application.  It has responsibilities for
 * * Creating and destroying the app window
 * * Processing game events
 */
class SFApp {
public:
  SFApp(std::shared_ptr<SFWindow>);
  virtual ~SFApp();
  void    OnEvent(SFEvent &);
  int     OnExecute();
  void    OnUpdateWorld();
  void    OnRender();

  void    FireProjectile();
private:
  SDL_Surface           * surface;
  bool                    is_running;

  shared_ptr<SFWindow>       sf_window;

  shared_ptr<SFAsset>        player;
  shared_ptr<SFBoundingBox>  app_box;
  shared_ptr<SFAsset>        score_title;
  shared_ptr<SFAsset>        top_bar;
  shared_ptr<SFAsset>        gameover;
  list<shared_ptr<SFAsset> > projectiles;
  list<shared_ptr<SFAsset> > aliens;
  list<shared_ptr<SFAsset> > coins;
  //BG
  list<shared_ptr<SFAsset> > stars;
  //Score
  list<shared_ptr<SFAsset> > score0s;
  list<shared_ptr<SFAsset> > score1s;
  list<shared_ptr<SFAsset> > score2s;
  list<shared_ptr<SFAsset> > score3s;
  list<shared_ptr<SFAsset> > score4s;
  list<shared_ptr<SFAsset> > score5s;
  list<shared_ptr<SFAsset> > score6s;
  list<shared_ptr<SFAsset> > score7s;
  list<shared_ptr<SFAsset> > score8s;
  list<shared_ptr<SFAsset> > score9s;
  list<shared_ptr<SFAsset> > score00s;
  list<shared_ptr<SFAsset> > score10s;
  list<shared_ptr<SFAsset> > score20s;
  list<shared_ptr<SFAsset> > score30s;
  list<shared_ptr<SFAsset> > score40s;
  list<shared_ptr<SFAsset> > score50s;
  list<shared_ptr<SFAsset> > score60s;
  list<shared_ptr<SFAsset> > score70s;
  list<shared_ptr<SFAsset> > score80s;
  list<shared_ptr<SFAsset> > score90s;

  int fire;

  SFError OnInit();

  int tick;

};
#endif
