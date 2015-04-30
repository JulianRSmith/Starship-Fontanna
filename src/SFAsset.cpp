#include "SFAsset.h"

int SFAsset::SFASSETID=0;

SFAsset::SFAsset(SFASSETTYPE type, std::shared_ptr<SFWindow> window): type(type), sf_window(window) {
  this->id   = ++SFASSETID;

  switch (type) {
  case SFASSET_PLAYER:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/player.png");
    break;
  case SFASSET_PROJECTILE:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/projectile.png");
    break;
  case SFASSET_ALIEN:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/alien.png");
    break;
  case SFASSET_COIN:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/coin.png");
    break;
/////////////////////////////////////////////////////////////////////////////////////////////////////
  case SFASSET_GAMEOVER:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/gameover.png");
    break;
//////////////////////////////////////////////////////////////////////////////////////////////////////
  case SFASSET_STAR:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/star.png");
    break;
//////////////////////////////////////////////////////////////////////////////////////////////////////
  case SFASSET_SCORE_TITLE:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/score_title.png");
    break;
  case SFASSET_TOP_BAR:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/top_bar.png");
    break;
//////////////////////////////////////////////////////////////////////////////////////////////////////
  case SFASSET_SCORE_0:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/score_0.png");
    break;
  case SFASSET_SCORE_1:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/score_1.png");
    break;
  case SFASSET_SCORE_2:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/score_2.png");
    break;
  case SFASSET_SCORE_3:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/score_3.png");
    break;
  case SFASSET_SCORE_4:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/score_4.png");
    break;
  case SFASSET_SCORE_5:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/score_5.png");
    break;
  case SFASSET_SCORE_6:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/score_6.png");
    break;
  case SFASSET_SCORE_7:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/score_7.png");
    break;
  case SFASSET_SCORE_8:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/score_8.png");
    break;
  case SFASSET_SCORE_9:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/score_9.png");
    break;
  case SFASSET_SCORE_00:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/score_00.png");
    break;
    case SFASSET_SCORE_10:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/score_10.png");
    break;
  case SFASSET_SCORE_20:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/score_20.png");
    break;
  case SFASSET_SCORE_30:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/score_30.png");
    break;
  case SFASSET_SCORE_40:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/score_40.png");
    break;
  case SFASSET_SCORE_50:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/score_50.png");
    break;
  case SFASSET_SCORE_60:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/score_60.png");
    break;
  case SFASSET_SCORE_70:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/score_70.png");
    break;
  case SFASSET_SCORE_80:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/score_80.png");
    break;
  case SFASSET_SCORE_90:
    sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/score_90.png");
    break;
  }

  if(!sprite) {
    cerr << "Could not load asset of type " << type << endl;
    throw SF_ERROR_LOAD_ASSET;
  }

  // Get texture width & height
  int w, h;
  SDL_QueryTexture(sprite, NULL, NULL, &w, &h);

  // Initialise bounding box
  bbox = make_shared<SFBoundingBox>(SFBoundingBox(Vector2(0.0f, 0.0f), w, h));
}

SFAsset::SFAsset(const SFAsset& a) {
  sprite = a.sprite;
  sf_window = a.sf_window;
  bbox   = a.bbox;
  type   = a.type;
}

SFAsset::~SFAsset() {
  bbox.reset();
  if(sprite) {
    SDL_DestroyTexture(sprite);
    sprite = nullptr;
  }
}

/**
 * The logical coordinates in the game assume that the screen
 * is indexed from 0,0 in the bottom left corner.  The blittable
 * coordinates of the screen map 0,0 to the top left corner. We
 * need to convert between the two coordinate spaces.  We assume
 * that there is a 1-to-1 quantisation.
 */
Vector2 GameSpaceToScreenSpace(SDL_Renderer* renderer, Vector2 &r) {
  int w, h;
  SDL_GetRendererOutputSize(renderer, &w, &h);

  return Vector2 (
                  r.getX(),
                  (h - r.getY())
                  );
}

void SFAsset::SetPosition(Point2 & point) {
  Vector2 v(point.getX(), point.getY());
  bbox->SetCentre(v);
}

Point2 SFAsset::GetPosition() {
  return Point2(bbox->centre->getX(), bbox->centre->getY());
}

SFAssetId SFAsset::GetId() {
  return id;
}

void SFAsset::OnRender() {
  // 1. Get the SDL_Rect from SFBoundingBox
  SDL_Rect rect;

  Vector2 gs = (*(bbox->centre) + (*(bbox->extent_x) * -1)) + (*(bbox->extent_y) * -1);
  Vector2 ss = GameSpaceToScreenSpace(sf_window->getRenderer(), gs);
  rect.x = ss.getX();
  rect.y = ss.getY();
  rect.w = bbox->extent_x->getX() * 2;
  rect.h = bbox->extent_y->getY() * 2;

  // 2. Blit the sprite onto the level
  SDL_RenderCopy(sf_window->getRenderer(), sprite, NULL, &rect);
}

void SFAsset::GoWest() {
  Vector2 c = *(bbox->centre) + Vector2(-10.0f, 0.0f);
  if(!(c.getX() < 30)) {
    bbox->centre.reset();
    bbox->centre = make_shared<Vector2>(c);
  }
}

void SFAsset::GoEast() {
  int w, h;
  SDL_GetRendererOutputSize(sf_window->getRenderer(), &w, &h);

  Vector2 c = *(bbox->centre) + Vector2(10.0f, 0.0f);
  if(!(c.getX() > 610)) {
    bbox->centre.reset();
    bbox->centre = make_shared<Vector2>(c);
  }
}

void SFAsset::GoNorth() {
  Vector2 c = *(bbox->centre) + Vector2(0.0f, 10.0f);
  bbox->centre.reset();
  bbox->centre = make_shared<Vector2>(c);
}

void SFAsset::PlayerGoNorth() {
  Vector2 c = *(bbox->centre) + Vector2(0.0f, 10.0f);
  if(!(c.getY() > 472 )) {
  bbox->centre.reset();
  bbox->centre = make_shared<Vector2>(c);
  }
}

void SFAsset::GoSouth() {
  Vector2 c = *(bbox->centre) + Vector2(0.0f, -3.0f);
  bbox->centre.reset();
  bbox->centre = make_shared<Vector2>(c);
}

void SFAsset::GoSouthStars() {
  Vector2 c = *(bbox->centre) + Vector2(0.0f, -4.0f);
  bbox->centre.reset();
  bbox->centre = make_shared<Vector2>(c);
}

void SFAsset::PlayerGoSouth() {
  Vector2 c = *(bbox->centre) + Vector2(0.0f, -10.0f);
  if(!(c.getY() < 66 )) {
  bbox->centre.reset();
  bbox->centre = make_shared<Vector2>(c);
  }
}

bool SFAsset::CollidesWith(shared_ptr<SFAsset> other) {
  return bbox->CollidesWith(other->bbox);
}

shared_ptr<SFBoundingBox> SFAsset::GetBoundingBox() {
  return bbox;
}

void SFAsset::SetNotAlive() {
  type = SFASSET_DEAD;
}

bool SFAsset::IsAlive() {
  return (SFASSET_DEAD != type);
}

void SFAsset::HandleCollision() {
  if(SFASSET_PROJECTILE == type || SFASSET_ALIEN == type || SFASSET_PLAYER == type) {
    SetNotAlive();
  }
}
