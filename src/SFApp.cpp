#include "SFApp.h"

  //Playerscore
  int playerscore = 0;
  int gameoverbool = 0;
  int gamewincount = 0;

SFApp::SFApp(std::shared_ptr<SFWindow> window) : fire(0), is_running(true), sf_window(window) {
  int canvas_w, canvas_h;
  SDL_GetRendererOutputSize(sf_window->getRenderer(), &canvas_w, &canvas_h);


  app_box = make_shared<SFBoundingBox>(Vector2(canvas_w, canvas_h), canvas_w, canvas_h);
  player  = make_shared<SFAsset>(SFASSET_PLAYER, sf_window);
  auto player_pos = Point2(canvas_w/2, 88.0f);
  player->SetPosition(player_pos);

////////////////////////////////////////////////////////////////////////////////////////
  const int number_of_stars = 640;
  int s=0; 

  while (s<number_of_stars) {
    // place an alien at width/number_of_aliens * i
    auto star    = make_shared<SFAsset>(SFASSET_STAR, sf_window);
    auto starpos = Point2((canvas_w/number_of_stars) * s, rand() % 16000 + 1 );
    star->SetPosition(starpos);
    stars.push_back(star);

    s++;
  }
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////GAME OVER///////////////////////////////////////////////////////
  gameover         = make_shared<SFAsset>(SFASSET_GAME_OVER, sf_window);
  auto gameoverpos = Point2(320,700);
  gameover->SetPosition(gameoverpos);
/////////////////////////////GAME WIN///////////////////////////////////////////////////////
  gamewin          = make_shared<SFAsset>(SFASSET_GAME_WIN, sf_window);
  auto gamewinpos  = Point2(320,700);
  gamewin->SetPosition(gamewinpos);
/////////////////////////////////////////////////////////////////////////////////////////////


  const int number_of_aliens = 90;
  int i=0; 

  while (i<number_of_aliens) {
    // place an alien at width/number_of_aliens * i
    auto alien = make_shared<SFAsset>(SFASSET_ALIEN, sf_window);
    auto apos  = Point2((canvas_w/number_of_aliens) * i, rand() % 14000 + 800 );
    alien->SetPosition(apos);
    aliens.push_back(alien);

    i++;
  }

  const int number_of_coins = 30;
  int j=0; 

  while (j<number_of_coins) {
    auto coin  = make_shared<SFAsset>(SFASSET_COIN, sf_window);
    auto cpos  = Point2((canvas_w/number_of_coins) * j, rand() % 14000 + 1200);
    coin->SetPosition(cpos);
    coins.push_back(coin);
    j++;
  }

  // Grey Score Bar
  top_bar     = make_shared<SFAsset>(SFASSET_TOP_BAR, sf_window);
  auto barpos = Point2(320,496);
  top_bar->SetPosition(barpos);

  //Score Title
  score_title = make_shared<SFAsset>(SFASSET_SCORE_TITLE, sf_window);
  auto spos   = Point2(429,485);
  score_title->SetPosition(spos);


  //////////////////////////////////////////////////////////////////////////////////////////
  /// SCORE NUMBERS///
  //////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////100ths/////////////////////
  /// SCORE 0 - YNN
  auto score_0 = make_shared<SFAsset>(SFASSET_SCORE_0, sf_window);
  auto scorepos1     = Point2(508,484);
  score_0->SetPosition(scorepos1);
  score0s.push_back(score_0);
  /// SCORE 100 - YYY
  auto score_1 = make_shared<SFAsset>(SFASSET_SCORE_1, sf_window);
  auto scorepos11     = Point2(508,484);
  score_1->SetPosition(scorepos11);
  score1s.push_back(score_1);
  /// SCORE 200 - YYY
  auto score_2 = make_shared<SFAsset>(SFASSET_SCORE_2, sf_window);
  auto scorepos21     = Point2(508,484);
  score_2->SetPosition(scorepos21);
  score2s.push_back(score_2);
  /// SCORE 300 - YNN
  auto score_3 = make_shared<SFAsset>(SFASSET_SCORE_3, sf_window);
  auto scorepos31     = Point2(508,484);
  score_3->SetPosition(scorepos31);
  score3s.push_back(score_3);
  /// SCORE 400 - YYY
  auto score_4 = make_shared<SFAsset>(SFASSET_SCORE_4, sf_window);
  auto scorepos41     = Point2(508,484);
  score_4->SetPosition(scorepos41);
  score4s.push_back(score_4);
  /// SCORE 500 - YYY
  auto score_5 = make_shared<SFAsset>(SFASSET_SCORE_5, sf_window);
  auto scorepos51     = Point2(508,484);
  score_5->SetPosition(scorepos51);
  score5s.push_back(score_5 );
  /// SCORE 600 - YYY
  auto score_6 = make_shared<SFAsset>(SFASSET_SCORE_6, sf_window);
  auto scorepos61     = Point2(508,484);
  score_6->SetPosition(scorepos61);
  score6s.push_back(score_6);
  /// SCORE 700 - YYY
  auto score_7 = make_shared<SFAsset>(SFASSET_SCORE_7, sf_window);
  auto scorepos71     = Point2(508,484);
  score_7->SetPosition(scorepos71);
  score7s.push_back(score_7);
  /// SCORE 800 - YNN
  auto score_8 = make_shared<SFAsset>(SFASSET_SCORE_8, sf_window);
  auto scorepos81     = Point2(508,484);
  score_8->SetPosition(scorepos81);
  score8s.push_back(score_8);
  /// SCORE 900 - YYY
  auto score_9 = make_shared<SFAsset>(SFASSET_SCORE_9, sf_window);
  auto scorepos91     = Point2(508,484);
  score_9->SetPosition(scorepos91);
  score9s.push_back(score_9);
  ////////////////////10ths/////////////////////
  /// SCORE 00 - YNN
  auto score_00 = make_shared<SFAsset>(SFASSET_SCORE_00, sf_window);
  auto scorepos2    = Point2(539,484);
  score_00->SetPosition(scorepos2);
  score00s.push_back(score_00);
  /// SCORE 10 - YNN
  auto score_10 = make_shared<SFAsset>(SFASSET_SCORE_10, sf_window);
  auto scorepos12   = Point2(539,484);
  score_10->SetPosition(scorepos12);
  score10s.push_back(score_10);
  /// SCORE 20 - YNN
  auto score_20 = make_shared<SFAsset>(SFASSET_SCORE_20, sf_window);
  auto scorepos22   = Point2(539,484);
  score_20->SetPosition(scorepos22);
  score20s.push_back(score_20);
  /// SCORE 30 - YNN
  auto score_30 = make_shared<SFAsset>(SFASSET_SCORE_30, sf_window);
  auto scorepos32   = Point2(539,484);
  score_30->SetPosition(scorepos32);
  score30s.push_back(score_30);
  /// SCORE 40 - YNN
  auto score_40 = make_shared<SFAsset>(SFASSET_SCORE_40, sf_window);
  auto scorepos42   = Point2(539,484);
  score_40->SetPosition(scorepos42);
  score40s.push_back(score_40);
  /// SCORE 50 - YNN
  auto score_50 = make_shared<SFAsset>(SFASSET_SCORE_50, sf_window);
  auto scorepos52   = Point2(539,484);
  score_50->SetPosition(scorepos52);
  score50s.push_back(score_50);
  /// SCORE 60 - YNN
  auto score_60 = make_shared<SFAsset>(SFASSET_SCORE_60, sf_window);
  auto scorepos62   = Point2(539,484);
  score_60->SetPosition(scorepos62);
  score60s.push_back(score_60);
  /// SCORE 70 - YNN
  auto score_70 = make_shared<SFAsset>(SFASSET_SCORE_70, sf_window);
  auto scorepos72   = Point2(539,484);
  score_70->SetPosition(scorepos72);
  score70s.push_back(score_70);
  /// SCORE 80 - YNN
  auto score_80 = make_shared<SFAsset>(SFASSET_SCORE_80, sf_window);
  auto scorepos82   = Point2(539,484);
  score_80->SetPosition(scorepos82);
  score80s.push_back(score_80);
  /// SCORE 90 - YNN
  auto score_90 = make_shared<SFAsset>(SFASSET_SCORE_90, sf_window);
  auto scorepos92   = Point2(539,484);
  score_90->SetPosition(scorepos92);
  score90s.push_back(score_90);



}




SFApp::~SFApp() {
}


/**
 * Handle all events that come from SDL.
 * These are timer or keyboard events.
 */
void SFApp::OnEvent(SFEvent& event) {
  SFEVENT the_event = event.GetCode();
  switch (the_event) {
  case SFEVENT_QUIT:
    is_running = false;
    break;
  case SFEVENT_UPDATE:
    OnUpdateWorld();
    OnRender();
    break;
  case SFEVENT_PLAYER_LEFT:
       player->GoWest();
    break;
  case SFEVENT_PLAYER_RIGHT:
    player->GoEast();
    break;
  case SFEVENT_PLAYER_UP:
    player->PlayerGoNorth();
    break;
  case SFEVENT_PLAYER_DOWN:
    player->PlayerGoSouth();
    break;
  case SFEVENT_FIRE:
    fire ++;
    FireProjectile();
    break;
  }
}


int SFApp::OnExecute() {
  // Execute the app
  SDL_Event event;
  while (SDL_WaitEvent(&event) && is_running) {
    // if this is an update event, then handle it in SFApp,
    // otherwise punt it to the SFEventDispacher.
    SFEvent sfevent((const SDL_Event) event);
    OnEvent(sfevent);
  }
}

void SFApp::OnUpdateWorld() {
  // Update projectile positions
  for(auto p: projectiles) {
    p->GoNorth();
}
 
  for (auto s: stars) {
    s->GoSouthStars();
}

  for(auto c: coins) {
    c->GoSouth();
  }

  // Update enemy positions
  for(auto a : aliens) {
     a->GoSouth();
     auto alienpos = a->GetPosition();
     if ( alienpos.getY() < 0 ) {
     gamewincount++;
     a->HandleCollision();
}
}

  // Detect collisions
  for(auto p : projectiles) {
    for(auto a : aliens) {
      auto projectilepos = p->GetPosition();
      if(p->CollidesWith(a) && projectilepos.getY() < 472 ) {
        p->HandleCollision();
        a->HandleCollision();
        // Add to score
        playerscore = playerscore + 10;
        gamewincount++;
	
      }
   for(auto c : coins) {
      if(player->CollidesWith(c)) {
        player->HandleCollision();
        c->HandleCollision();
        gameoverbool = 1;
      }
    }
  }
  // remove dead aliens (the long way)
  list<shared_ptr<SFAsset>> tmp;
  for(auto a : aliens) {
    if(a->IsAlive()) {
      tmp.push_back(a);
    }
  }
  aliens.clear();
  aliens = list<shared_ptr<SFAsset>>(tmp);
}
list<shared_ptr<SFAsset>> tmp;
for(auto c : coins) {
    if(c->IsAlive()) {
      tmp.push_back(c);
    }
  }
  coins.clear();
  coins = list<shared_ptr<SFAsset>>(tmp);
}

void SFApp::OnRender() {
  SDL_RenderClear(sf_window->getRenderer());

////DRAW BG///////////////////////////////////////////////////////////////////
for (auto s: stars) {
 s->OnRender();
}
/////////////////////////////////////////

  // draw the player
  player->OnRender();


  for(auto p: projectiles) {
    if(p->IsAlive()) {p->OnRender();}
    else { fire--;    
         }
  }

  for(auto a: aliens) {
    if(a->IsAlive()) {a->OnRender();}
  }

  for(auto c: coins) {
if (gameoverbool == 0) {
    c->OnRender();
}
  }

//////////////////////////////////////////////////////////////////////////////
if (gameoverbool == 1) {
 gameover->OnRender();
 cout<< "GAMEOVER"<< endl;
 cout<< "Your Score = ";
 cout<< playerscore << endl;
}
if (gameoverbool == 0 && gamewincount >= 90 ) {
 gamewin->OnRender();
 cout<< "WELL DONE! YOU WON"<< endl;
 cout<< "Your Score = ";
cout<< playerscore << endl;
}

    //Draw top bar
  top_bar->OnRender();

  //Draw Score title
  score_title->OnRender();

  //Score System
  /////100ths/////
  for (auto s0: score0s)
  if (playerscore < 99) {
      s0->OnRender();
  }
  for (auto s1: score1s)
  if (playerscore >= 100) {
      s1->OnRender();
  }
  for (auto s2: score2s)
  if (playerscore >= 200) {
      s2->OnRender();
  }
  for (auto s3: score3s)
  if (playerscore >= 300) {
      s3->OnRender();
  }

  for (auto s4: score4s)
  if (playerscore >= 400) {
      s4->OnRender();
  }
  for (auto s5: score5s)
  if (playerscore >= 500) {
      s5->OnRender();
  }
    for (auto s6: score6s)
  if (playerscore >= 600) {
      s6->OnRender();
  }
  for (auto s7: score7s)
  if (playerscore >= 700) {
      s7->OnRender();
  }
  for (auto s8: score8s)
  if (playerscore >= 800) {
      s8->OnRender();
  }
  for (auto s9: score9s)
  if (playerscore >= 900) {
      s9->OnRender();
  }
  /////10ths/////
  for (auto s00: score00s)
    if (playerscore == 0 || playerscore == 100 || playerscore == 200 || playerscore == 300 || playerscore == 400 || playerscore == 500 || playerscore == 600 || playerscore == 700 || playerscore == 800 || playerscore == 900 ) {
      s00->OnRender();
  }
  for (auto s10: score10s)
    if (playerscore == 10 || playerscore == 110 || playerscore == 210 || playerscore == 310 || playerscore == 410 || playerscore == 510 || playerscore == 610 || playerscore == 710 || playerscore == 810 || playerscore == 910 ) {
      s10->OnRender();
  }
  for (auto s20: score20s)
    if (playerscore == 20 || playerscore == 120 || playerscore == 220 || playerscore == 320 || playerscore == 420 || playerscore == 520 || playerscore == 620 || playerscore == 720 || playerscore == 820 || playerscore == 920 ) {
      s20->OnRender();
  }
  for (auto s30: score30s)
    if (playerscore == 30 || playerscore == 130 || playerscore == 230 || playerscore == 330 || playerscore == 430 || playerscore == 530 || playerscore == 630 || playerscore == 730 || playerscore == 830 || playerscore == 930 ) {
      s30->OnRender();
  }
  for (auto s40: score40s)
    if (playerscore == 40 || playerscore == 140 || playerscore == 240 || playerscore == 340 || playerscore == 440 || playerscore == 540 || playerscore == 640 || playerscore == 740 || playerscore == 840 || playerscore == 940 ) {
      s40->OnRender();
  }
  for (auto s50: score50s)
    if (playerscore == 50 || playerscore == 150 || playerscore == 250 || playerscore == 350 || playerscore == 450 || playerscore == 550 || playerscore == 650 || playerscore == 750 || playerscore == 850 || playerscore == 950 ) {
      s50->OnRender();
  }
  for (auto s60: score60s)
    if (playerscore == 60 || playerscore == 160 || playerscore == 260 || playerscore == 360 || playerscore == 460 || playerscore == 560 || playerscore == 660 || playerscore == 760 || playerscore == 860 || playerscore == 960 ) {
      s60->OnRender();
  }

  for (auto s70: score70s)
    if (playerscore == 70 || playerscore == 170 || playerscore == 270 || playerscore == 370 || playerscore == 470 || playerscore == 570 || playerscore == 670 || playerscore == 770 || playerscore == 870 || playerscore == 970 ) {
      s70->OnRender();
  }
  for (auto s80: score80s)
    if (playerscore == 80 || playerscore == 180 || playerscore == 280 || playerscore == 380 || playerscore == 480 || playerscore == 580 || playerscore == 680 || playerscore == 780 || playerscore == 880 || playerscore == 980 ) {
      s80->OnRender();
  }
  for (auto s90: score90s)
    if (playerscore == 90 || playerscore == 190 || playerscore == 290 || playerscore == 390 || playerscore == 490 || playerscore == 590 || playerscore == 690 || playerscore == 790 || playerscore == 890 || playerscore == 990 ) {
      s90->OnRender();
  }


  // Switch the off-screen buffer to be on-screen
  SDL_RenderPresent(sf_window->getRenderer());
}

void SFApp::FireProjectile() {
  auto pb = make_shared<SFAsset>(SFASSET_PROJECTILE, sf_window);
  auto v  = player->GetPosition();
  pb->SetPosition(v);
  projectiles.push_back(pb);
}
