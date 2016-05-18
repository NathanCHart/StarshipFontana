#include "SFApp.h"



SFApp::SFApp(std::shared_ptr<SFWindow> window) : score(0), fire(0), is_running(true), sf_window(window) {
  int canvas_w, canvas_h;
  SDL_GetRendererOutputSize(sf_window->getRenderer(), &canvas_w, &canvas_h);

  app_box = make_shared<SFBoundingBox>(Vector2(canvas_w, canvas_h), canvas_w, canvas_h);
  player  = make_shared<SFAsset>(SFASSET_PLAYER, sf_window);
  auto player_pos = Point2(canvas_w/2, 35);
  player->SetPosition(player_pos);

  const int number_of_aliens = 10;
  for(int i=0; i<number_of_aliens; i++) {
    // place an alien at width/number_of_aliens * i
    auto alien = make_shared<SFAsset>(SFASSET_ALIEN, sf_window);
    auto pos   = Point2((canvas_w/number_of_aliens) * i+30, 420.0f);
    alien->SetPosition(pos);
    aliens.push_back(alien);
  }

const int number_of_wallsx = 20;
  for(int i=0; i<number_of_wallsx; i++) {
    // place an alien at width/number_of_aliens * i
    auto wallsx = make_shared<SFAsset>(SFASSET_WALLX, sf_window);
    auto pos   = Point2((canvas_w/number_of_wallsx) * i, 5.0f);
    wallsx->SetPosition(pos);
    wallx.push_back(wallsx);
  }




const int number_of_wallsy = 20;
  for(int i=0; i<number_of_wallsy; i++) {
    // place an alien at width/number_of_aliens * i
    auto wallsy = make_shared<SFAsset>(SFASSET_WALLY, sf_window);
    auto pos   = Point2(5.0f, (canvas_w/number_of_wallsy) * i);
    wallsy->SetPosition(pos);
    wally.push_back(wallsy);
  }

const int number_of_wallsyright = 20;
  for(int i=0; i<number_of_wallsyright; i++) {
    // place an alien at width/number_of_aliens * i
    auto wallsy = make_shared<SFAsset>(SFASSET_WALLY, sf_window);
    auto pos   = Point2(635.0f, (canvas_w/number_of_wallsyright) * i);
    wallsy->SetPosition(pos);
    wally.push_back(wallsy);
  }

const int number_of_wallsxtop = 20;
  for(int i=0; i<number_of_wallsxtop; i++) {

    auto wallsx = make_shared<SFAsset>(SFASSET_WALLX, sf_window);
    auto pos   = Point2((canvas_w/number_of_wallsxtop) * i, 475.0f);
    wallsx->SetPosition(pos);
    wallx.push_back(wallsx);
  }

  auto coin = make_shared<SFAsset>(SFASSET_COIN, sf_window);
  auto pos  = Point2((canvas_w/4), 100);
  coin->SetPosition(pos);
  coins.push_back(coin);
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

for(auto wx : wallx) {
  if(player->CollidesWith(wx)) {
        player->HandleCollision();
        wx->HandleCollision();
	player->GoEast();
}
}

for(auto wy : wally) {
  if(player->CollidesWith(wy)) {
        player->HandleCollision();
        wy->HandleCollision();
	player->GoEast();
}
}

    break;

  case SFEVENT_PLAYER_RIGHT:
    player->GoEast();

for(auto wx : wallx) {
  if(player->CollidesWith(wx)) {
        player->HandleCollision();
        wx->HandleCollision();
	player->GoWest();
}
}

for(auto wy : wally) {
  if(player->CollidesWith(wy)) {
        player->HandleCollision();
        wy->HandleCollision();
	player->GoWest();
}
}

    break;
  case SFEVENT_PLAYER_UP:
    player->GoNorth();

for(auto wx : wallx) {
  if(player->CollidesWith(wx)) {
        player->HandleCollision();
        wx->HandleCollision();
	player->GoSouth();
}
}

for(auto wy : wally) {
  if(player->CollidesWith(wy)) {
        player->HandleCollision();
        wy->HandleCollision();
	player->GoSouth();
}
}
    break;
  case SFEVENT_PLAYER_DOWN:
    player->GoSouth();

for(auto wx : wallx) {
  if(player->CollidesWith(wx)) {
        player->HandleCollision();
        wx->HandleCollision();
	player->GoNorth();
}
}

for(auto wy : wally) {
  if(player->CollidesWith(wy)) {
        player->HandleCollision();
        wy->HandleCollision();
	player->GoNorth();
}
}
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
    // wrap an SDL_Event with our SFEvent
    SFEvent sfevent((const SDL_Event) event);
    // handle our SFEvent
    OnEvent(sfevent);
  }
}

void SFApp::OnUpdateWorld() {
  // Update projectile positions
  for(auto p: projectiles) {
    p->GoNorth();
  }

  for(auto c: coins) {
    c->GoNorth();
  }

  for (auto el: enemylaser){
	el->GoSouth();

}

int randomno;
int mov;

  // Update enemy positions

  for(auto a : aliens) {
    // do something here
	mov= rand() % 3;
	randomno= rand() % 1000;
	if (randomno == 50){

	FireEnemy();
}
       if(mov == 0){
	a->GoWest();
	for(auto wy : wally){
	if(a->CollidesWith(wy)){
	a->GoEast();
}
}
}
	 else if(mov == 1){
	a->GoEast();
	for(auto wy : wally){
	if(a->CollidesWith(wy)){
	a->GoWest();
}
}
}
	
	else if(mov == 2){
	a->GoSouthE();
}
	for(auto wx : wallx){
	if(a->CollidesWith(wx)){
	std::cout<<"GAME OVER"<<std::endl;
	is_running=false;
}
}

	if(a->CollidesWith(player)){
	std::cout<<"GAME OVER"<<std::endl;
	is_running=false;
}		 
}
		
  
int lives = 3;
  // Detect collisionshttp://www.github.comn/
  for(auto p : projectiles) {
    for(auto a : aliens) {
      if(p->CollidesWith(a)) {
        p->HandleCollision();
        a->HandleCollision();
        score= score+100;
        std::cout<<"Score = "<<score<<std::endl;
        
      }
      if(score==1000){
	 std::cout<<"Congratulations, you win!"<<std::endl;
         is_running = false;
}
    }
  }

  for(auto el : enemylaser) {
      if (el->CollidesWith(player)){
	el->HandleCollision();
	player->HandleCollision();
      std::cout<<"GAME OVER"<<std::endl;
      is_running=false;

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


  
void SFApp::OnRender() {
  SDL_RenderClear(sf_window->getRenderer());

  // draw the player
  player->OnRender();

  for(auto p: projectiles) {
    if(p->IsAlive()) {p->OnRender();}
  }

  for(auto a: aliens) {
    if(a->IsAlive()) {a->OnRender();}
  }
 
  for(auto el: enemylaser){
   if (el->IsAlive()) {el->OnRender();}
}

  for(auto c: coins) {
    c->OnRender();
  }

  for(auto wx: wallx) {
    wx->OnRender();
 }

 for(auto wy: wally) {
    wy->OnRender();

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

void SFApp::FireEnemy() {
  auto pe = make_shared<SFAsset>(SFASSET_ENEMYLASER, sf_window);
 for(auto a: aliens){
  auto q =  a->GetPosition();
  pe->SetPosition(q);
  enemylaser.push_back(pe);
}
}
