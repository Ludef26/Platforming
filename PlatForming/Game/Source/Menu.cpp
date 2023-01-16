#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "Window.h"
#include "Audio.h"
#include "Input.h"
#include "Scene.h"

#include "Menu.h"

#include "Map.h"
#include "Player.h"
#include "Defs.h"
#include "Log.h"


Menu::Menu(bool enabled) : Module(enabled)
{
	name.Create("menu");

	torch_selection_anim.PushBack({ 0,0,33,49 });
	torch_selection_anim.PushBack({ 35,0,33,49 });
	torch_selection_anim.PushBack({ 70,0,33,49 });
	torch_selection_anim.speed = 0.1f;
	torch_selection_anim.loop = true;

    torch_light_1_anim.PushBack({ 0,0,460,240 });
	torch_light_1_anim.PushBack({ 490,0,460,240 });
	torch_light_1_anim.PushBack({ 1000,0,460,240 });
	torch_light_1_anim.speed = 0.165f;
	torch_light_1_anim.loop = true;

	torch_light_2_anim.PushBack({ 0,0,570,182 });
	torch_light_2_anim.PushBack({ 566,0,570,182 });
	torch_light_2_anim.PushBack({ 1140,0,570,182 });
	torch_light_2_anim.speed = 0.165f;
	torch_light_2_anim.loop = true;

	torch_light_3_anim.PushBack({ 0,0,520,182 });
	torch_light_3_anim.PushBack({ 522,0,520,182 });
	torch_light_3_anim.PushBack({ 1023,0,520,182 });
	torch_light_3_anim.speed = 0.165f;
	torch_light_3_anim.loop = true;

	torch_light_4_anim.PushBack({ 0,0,318,167 });
	torch_light_4_anim.PushBack({ 318,0,318,167 });
	torch_light_4_anim.PushBack({ 660,0,318,167 });
	torch_light_4_anim.speed = 0.165f;
	torch_light_4_anim.loop = true;


	big_fire_anim.PushBack({ 244,0,231,720 });
	big_fire_anim.PushBack({ 475,0,400,720 });
	big_fire_anim.PushBack({ 0,0,244,720 });
	
	big_fire_anim.speed = 0.1f;
	big_fire_anim.loop = true;

	light_big_fire_anim.PushBack({ 4,0,518,405 });
	light_big_fire_anim.PushBack({ 533,0,563,405 });
	light_big_fire_anim.PushBack({ 1106,0,494,405 });
	light_big_fire_anim.speed = 0.165f;
	light_big_fire_anim.loop = true;


	smook_big_fire_anim.PushBack({ 0,0,226,490 });
	smook_big_fire_anim.PushBack({ 460,0,225,490 });
	smook_big_fire_anim.PushBack({ 238,0,217,490 });
	smook_big_fire_anim.speed = 0.06f;
	smook_big_fire_anim.loop = true;


	space_boton_anim.PushBack({ 10,0,195,121 });
	space_boton_anim.PushBack({ 226,0,201,121 });
	space_boton_anim.speed = 0.06f;
	space_boton_anim.loop = true;



	menu_play_anim.PushBack({ 31,0,286,597 });
	menu_play_anim.PushBack({ 345,0,290,597 });
	menu_play_anim.PushBack({ 681,0,286,597 });
	menu_play_anim.speed = 0.2f;
	menu_play_anim.loop = false;
}

// Destructor
Menu::~Menu()
{}

// Called before render is available
bool Menu::Awake()
{

	return true;
}

// Called before the first frame
bool Menu::Start()
{
	mama = app->tex->Load("Assets/Screens/Dying_scene.png");
	if (this->Enabled() && !this->Disabled())
	{
		r = { 0, 0, 1280, 720 };

		PauseMenuHUD = { 100, 500, 400, 720 }; //Cuadro Menu Pause

		paused = false;
		settings = false;
		win = false;
		lose = false;
		scape = false;
		slider = false;
		slider2 = false;
		fullscreen = false;
		vsync = false;
		credits = false;
		intro = false;
		subplaymenu = false;

		chosed = 0;
		app->win->GetWindowSize(win_w, win_h);

		open_book_sound = app->audio->LoadFx("Assets/audio/fx/open_book.wav");
		click_sound = app->audio->LoadFx("Assets/audio/fx/pop.wav");
		hover_sound = app->audio->LoadFx("Assets/audio/fx/hover.wav");
		win_sound = app->audio->LoadFx("Assets/audio/fx/win.wav");
		lose_sound = app->audio->LoadFx("Assets/audio/fx/lose.wav");

		for (size_t i = 0; i < NUM_PAUSE_BUTTONS; i++)
		{
			pause_buttons[i].rect.x = ((int)win_w / 2) - (pause_buttons[i].rect.w / 2);
			pause_buttons[i].rect.y = ((int)win_h / (NUM_PAUSE_BUTTONS + 1)) * (i + 1);
		}

		for (size_t i = 0; i < NUM_MENU_BUTTONS; i++)
		{
			menu_buttons[i].rect.x = ((int)win_w / 2) - (menu_buttons[i].rect.w / 2);
			menu_buttons[i].rect.y = ((int)win_h / (NUM_MENU_BUTTONS + 1)) * (i + 1);
		}

		for (size_t i = 0; i < NUM_SETTINGS_BUTTONS; i++)
		{
			settings_buttons[i].rect.x = ((int)win_w / 2) - (settings_buttons[i].rect.w / 2);
			settings_buttons[i].rect.y = ((int)win_h / (NUM_PAUSE_BUTTONS + 1)) * (i + 1);
		}

		whitemark_128x128 = app->tex->Load("Assets/textures/128x128_whitemark.png");
		whitemark_500x70 = app->tex->Load("Assets/textures/500x70_whitemark.png");
		whitemark_800x150 = app->tex->Load("Assets/textures/800x150_whitemark.png");
		whitemark_1240x680 = app->tex->Load("Assets/textures/1240x680_whitemark.png");
		skills_icons = app->tex->Load("Assets/textures/skill_icons.png");
		accept_tex = app->tex->Load("Assets/textures/accept_cancel.png");
		desc_icons = app->tex->Load("Assets/textures/descriptions_icons.png");
		rew_icons = app->tex->Load("Assets/textures/rewards.png");

		win_button.rect.w = 500;
		win_button.rect.x = ((int)win_w / 2) - (win_button.rect.w / 2);
		win_button.rect.y = (int)win_h / 2 + 200;

		lose_buttons[0].rect.w = 500;
		lose_buttons[0].rect.x = ((int)win_w / 2) - (lose_buttons[0].rect.w / 2) - 600;
		lose_buttons[0].rect.y = (int)win_h / 2 + 200;
		lose_buttons[1].rect.w = 500;
		lose_buttons[1].rect.x = ((int)win_w / 2) - (lose_buttons[1].rect.w / 2) + 600;
		lose_buttons[1].rect.y = (int)win_h / 2 + 200;

		scape_buttons[0].rect.w = 500;
		scape_buttons[0].rect.x = ((int)win_w / 2) - (lose_buttons[0].rect.w / 2) - 600;
		scape_buttons[0].rect.y = (int)win_h / 2 + 200;
		scape_buttons[1].rect.w = 500;
		scape_buttons[1].rect.x = ((int)win_w / 2) - (lose_buttons[1].rect.w / 2) + 600;
		scape_buttons[1].rect.y = (int)win_h / 2 + 200;

		pause_buttons[0].tex = app->tex->Load("Assets/textures/Continue_In_game.png"); // Continue
		pause_buttons[0].alt_tex_selec = app->tex->Load("Assets/textures/Fullscreen_No_Select.png");

		pause_buttons[1].tex = app->tex->Load("Assets/textures/Settings_In_game.png"); // Settings
		pause_buttons[1].alt_tex_selec = app->tex->Load("Assets/textures/Fullscreen_No_Select.png");

		pause_buttons[2].tex = app->tex->Load("Assets/textures/Back_In_game.png"); // Back to Menu
		pause_buttons[2].alt_tex_selec = app->tex->Load("Assets/textures/Fullscreen_No_Select.png");

		pause_buttons[3].tex = app->tex->Load("Assets/textures/Exit_In_game.png"); // Exit
		pause_buttons[3].alt_tex_selec = app->tex->Load("Assets/textures/Fullscreen_No_Select.png");

		//----------------------------------------------------------------MENU INICIO BOTONES------------------------
		menu_buttons[0].alt_tex = app->tex->Load("Assets/textures/PlaySprite.png"); // Play
		menu_buttons[0].tex = app->tex->Load("Assets/textures/PlayDarkSprite.png"); // Play

		//menu_buttons[0].alt_tex = app->tex->Load("Assets/textures/Continue.png"); // Continue

		menu_buttons[1].alt_tex = app->tex->Load("Assets/textures/SettingsSprite.png"); // Settings
		menu_buttons[1].tex = app->tex->Load("Assets/textures/SettingsDarkSprite.png"); // Settings

		menu_buttons[2].alt_tex = app->tex->Load("Assets/textures/CreditsSprite.png"); // Credits
		menu_buttons[2].tex = app->tex->Load("Assets/textures/CreditsDarkSprite.png"); // Credits

		//menu_buttons[2].alt_tex = app->tex->Load("Assets/textures/CreditsImage.png"); // Credits

		menu_buttons[3].alt_tex = app->tex->Load("Assets/textures/ExitSprite.png"); // Exit
		menu_buttons[3].tex = app->tex->Load("Assets/textures/ExitDarkSprite.png"); // Exit


		menu_buttons[4].tex = app->tex->Load("Assets/textures/ContinueBlackSprite.png"); // Credits
		menu_buttons[4].alt_tex = app->tex->Load("Assets/textures/ContinueSprite.png"); // Credits
		menu_buttons[4].alt_tex2 = app->tex->Load("Assets/textures/Fx.png");

		menu_buttons[5].tex = app->tex->Load("Assets/textures/NewGameBlackSprite.png"); // Credits
		menu_buttons[5].alt_tex = app->tex->Load("Assets/textures/NewGameSprite.png"); // Credits
		//----------------------------------------------------------------

		settings_buttons[0].alt_tex = settings_buttons[1].alt_tex = app->tex->Load("Assets/textures/Slider.png"); // Slider

		settings_buttons[0].tex = app->tex->Load("Assets/textures/Sound.png"); // Audio
		settings_buttons[0].alt_tex_selec = app->tex->Load("Assets/textures/Fullscreen_No_Select.png");
		settings_buttons[0].alt_tex2 = app->tex->Load("Assets/textures/SoundSprite.png");

		settings_buttons[1].tex = app->tex->Load("Assets/textures/Fx.png"); // Fx slider
		settings_buttons[1].alt_tex_selec = app->tex->Load("Assets/textures/Fullscreen_No_Select.png");
		settings_buttons[1].alt_tex2 = app->tex->Load("Assets/textures/FxSprite.png");

		settings_buttons[2].tex = app->tex->Load("Assets/textures/Fullscreen_no.png"); // Fullscreen No
		settings_buttons[2].alt_tex_selec = app->tex->Load("Assets/textures/Fullscreen_No_Select.png"); // Fullscreen No Selec
		settings_buttons[2].alt_tex = app->tex->Load("Assets/textures/Fullscreen_si.png"); // Fullscreen Si


		settings_buttons[3].tex = app->tex->Load("Assets/textures/Vsync_no.png"); // Vsync No
		settings_buttons[3].alt_tex_selec = app->tex->Load("Assets/textures/Fullscreen_No_Select.png");
		settings_buttons[3].alt_tex = app->tex->Load("Assets/textures/Vsync_si.png"); // Vsync Si



		win_button.tex = app->tex->Load("Assets/textures/Close_Buton_Win.png"); // Return field
		win_button.alt_tex = app->tex->Load("Assets/textures/Close_Buton_Win_Select.png"); // Return field
	
		lose_buttons[0].tex = app->tex->Load("Assets/textures/Retry_Buton_Lose.png"); // Try again
		lose_buttons[0].alt_tex = app->tex->Load("Assets/textures/Retry_Buton_Lose_Select.png"); // Try again

		lose_buttons[1].tex = app->tex->Load("Assets/textures/Run_Boton_Lose.png"); // Return field
		lose_buttons[1].alt_tex = app->tex->Load("Assets/textures/Run_Boton_Lose_Select.png"); // Return field

		Scape_BackGround = app->tex->Load("Assets/textures/Temporal_Background.png");
		Lose_BackGround = app->tex->Load("Assets/textures/Lose_Screen.png");
		Win_BackGround = app->tex->Load("Assets/textures/Win_Screen.png");

		combat_scape = app->tex->Load("Assets/textures/scape_text.png");

		torch_fire = app->tex->Load("Assets/textures/Torch_Fire.png");
		light_fire1 = app->tex->Load("Assets/textures/Torch1_light.png");
		light_fire2 = app->tex->Load("Assets/textures/Torch2_light.png");
		light_fire3 = app->tex->Load("Assets/textures/Torch3_light.png");
		light_fire4 = app->tex->Load("Assets/textures/Torch4_light.png");

		big_fire = app->tex->Load("Assets/textures/Big_Fire.png");
		big_fire_light = app->tex->Load("Assets/textures/Big_Fire_Light.png");
		smook_big_fire = app->tex->Load("Assets/textures/Smoke.png");

		space_boton = app->tex->Load("Assets/textures/Space_Boton_Anim.png");

		menu_in_game = app->tex->Load("Assets/textures/OpcionesInGame.png");

		menu_play = app->tex->Load("Assets/textures/Menu_Play.png");

		team_photo = app->tex->Load("Assets/textures/TeamPhoto.png");

		creditsTexture = app->tex->Load("Assets/textures/Creditos.png");

		hover_playing = false;

		// unlock animation
		unlock_cd = 120;
		unlock_state = 0;
		unlock_pos = { 576, 200 };
		unlock_rect = { 0, 0, 128, 128 };
		unknow_tex = app->tex->Load("Assets/textures/unknow.png");
		gear_tex = app->tex->Load("Assets/textures/gear.png");
		items_tex = app->tex->Load("Assets/textures/Objects/items.png");
		object_buttons[0].rect.w = 500;
		object_buttons[1].rect.w = 500;
		unlock_fx = app->audio->LoadFx("Assets/audio/fx/unlock.wav");
		equip_sound = app->audio->LoadFx("Assets/audio/fx/equip.wav");

		sub_newgame = false;
		for (size_t i = 0; i < NUM_ASK_BUTTONS; i++)
		{
			ask_buttons[i].rect.w = 128;
			ask_buttons[i].rect.h = 128;
		}

		count_xp = false;
		xp0 = 0;
		xp1 = 0;
		xp2 = 0;
		xp3 = 0;
		pugi::xml_document saveGame;
		axp0 = saveGame.child("objects").child("assassin").child("experience").attribute("value").as_int();
		axp1 = saveGame.child("objects").child("healer").child("experience").attribute("value").as_int();
		axp2 = saveGame.child("objects").child("tank").child("experience").attribute("value").as_int();
		axp3 = saveGame.child("objects").child("wizard").child("experience").attribute("value").as_int();

		cursor_tex = app->tex->Load("Assets/textures/cursor_default.png");
	}

	return true;
}

// Called each loop iteration
bool Menu::PreUpdate()
{
	intro = !started;

	if (!InAnyButton())
	{
		hover_playing = false;
	}
	
	
	
	
	
	


	
	




	if (intro && (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_X) == KEY_UP))
		credits = false;

	if (settings && (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_X) == KEY_UP))
	{
		quitarOpciones = true;
	}

	if (subplaymenu && (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_X) == KEY_UP))
	{
		subplaymenu = false;
	}

	else
	{
		description_disabled = true;
	}
	
	return true;
}

// Called each loop iteration
bool Menu::Update(float dt)
{
	// ------------------------------------- Anims Update
	torch_selection_anim.Update();
	torch_light_1_anim.Update();
	torch_light_2_anim.Update();
	torch_light_3_anim.Update();
	torch_light_4_anim.Update();

	big_fire_anim.Update();
	light_big_fire_anim.Update();
	smook_big_fire_anim.Update();
	space_boton_anim.Update();

	// -----------------------------------------------------textura de perder
	rect = { 0, 0, 640, 640 };
	app->render->DrawTexture(mama, 100 + (315 * 0), 450, &rect);
	//-------------------------------------------------------
	return true;
}

// Called each loop iteration
bool Menu::PostUpdate()
{
	int c_x = -app->render->camera.x;
	int c_y = -app->render->camera.y;
	
	r.x = c_x;
	r.y = c_y;

	//---------------------------------------------------------HUD PAUSE---------------------------------------------
	//Dimensiones Hud Pause
	PauseMenuHUD.x = c_x+ c_x_menu;
	PauseMenuHUD.y = c_y;


	SDL_Rect rect;
	if (win)
	{
		app->render->DrawTexture(Win_BackGround, c_x, c_y);
		//app->render->DrawTexture(combat_win, c_x, c_y);

		win_button.rect.x = ((int)win_w / 2) - (win_button.rect.w / 2) + c_x+530;
		win_button.rect.y = (int)win_h / 2 + 200 + c_y-370;

		if (win_button.state == 0)
		{
			app->render->DrawTexture(win_button.tex, win_button.rect.x , win_button.rect.y);
		}

		else if (win_button.state == 1)
		{
			app->render->DrawTexture(win_button.alt_tex, win_button.rect.x - 20 , win_button.rect.y - 20);
		}

		rect = { 0, 0, 64, 64 };
		
		rect = { 64, 0, 64, 64 };
		for (size_t i = 0; i < 4; i++)
		{
			app->render->DrawTexture(rew_icons, 100 + (315 * i), 550, &rect);
		}
	}

	if (lose)
	{
		app->render->DrawTexture(Lose_BackGround, c_x, c_y);
		//app->render->DrawTexture(combat_lose, c_x, c_y);

		lose_buttons[0].rect.x = ((int)win_w / 2) - (lose_buttons[0].rect.w / 2) + c_x-400;
		lose_buttons[0].rect.y = (int)win_h / 2  + c_y;
		lose_buttons[0].rect.w = 200;
		lose_buttons[0].rect.h = 100;

		lose_buttons[1].rect.x = ((int)win_w / 2) - (lose_buttons[1].rect.w / 2)  + c_x+280;
		lose_buttons[1].rect.y = (int)win_h / 2  + c_y + 130;
		lose_buttons[1].rect.w = 200;
		lose_buttons[1].rect.h = 100;

		for (size_t i = 0; i < NUM_LOSE_BUTTONS; i++)
		{
			//Retry button
			if (lose_buttons[0].state == 0)
			{
				//rect = { 0, 0, 500, 70 };
				app->render->DrawTexture(lose_buttons[0].tex, lose_buttons[0].rect.x, lose_buttons[0].rect.y);
			}
			else if (lose_buttons[0].state == 1)
			{
				//rect = { 0, 70, 500, 70 };
				app->render->DrawTexture(lose_buttons[0].alt_tex, lose_buttons[0].rect.x - 20, lose_buttons[0].rect.y - 20);
			}

			//Run button
			if (lose_buttons[1].state == 0)
			{
				//rect = { 0, 0, 500, 70 };
				app->render->DrawTexture(lose_buttons[1].tex, lose_buttons[1].rect.x, lose_buttons[1].rect.y);
			}
			else if (lose_buttons[1].state == 1)
			{
				//rect = { 0, 70, 500, 70 };
				app->render->DrawTexture(lose_buttons[1].alt_tex, lose_buttons[1].rect.x-20, lose_buttons[1].rect.y-20);
			}
			else if (lose_buttons[i].state == 2)
			{
				//rect = { 0, 140, 500, 70 };
				//app->render->DrawTexture(whitemark_500x70, lose_buttons[i].rect.x, lose_buttons[i].rect.y, &rect);
			}
		}

		rect = { 0, 0, 64, 64 };
		app->render->DrawTexture(rew_icons, 550, 300, &rect);
	
		//app->fonts->BlitText(lose_buttons[0].rect.x, lose_buttons[0].rect.y + 15, app->fonts->textFont1, "restart battle");
		//app->fonts->BlitText(lose_buttons[1].rect.x, lose_buttons[1].rect.y + 15, app->fonts->textFont1, "return to field");
	}

	if (scape)
	{
		app->render->DrawTexture(Scape_BackGround, c_x, c_y);
		app->render->DrawTexture(combat_scape, c_x, c_y);

		scape_buttons[0].rect.x = ((int)win_w / 2) - (scape_buttons[0].rect.w / 2) - 300 + c_x;
		scape_buttons[0].rect.y = (int)win_h / 2 + 200 + c_y;
		scape_buttons[1].rect.x = ((int)win_w / 2) - (scape_buttons[1].rect.w / 2) + 300 + c_x;
		scape_buttons[1].rect.y = (int)win_h / 2 + 200 + c_y;

		for (size_t i = 0; i < NUM_SCAPE_BUTTONS; i++)
		{
			if (scape_buttons[i].state == 0)
			{
				rect = { 0, 0, 500, 70 };
				app->render->DrawTexture(whitemark_500x70, scape_buttons[i].rect.x, scape_buttons[i].rect.y, &rect);
			}
			else if (scape_buttons[i].state == 1)
			{
				rect = { 0, 70, 500, 70 };
				app->render->DrawTexture(whitemark_500x70, scape_buttons[i].rect.x, scape_buttons[i].rect.y, &rect);
			}
			else if (scape_buttons[i].state == 2)
			{
				rect = { 0, 140, 500, 70 };
				app->render->DrawTexture(whitemark_500x70, scape_buttons[i].rect.x, scape_buttons[i].rect.y, &rect);
			}
		}

	
	}

	

	if (unlock_state != 0)
	{
		SDL_Rect or = { 0, 0, 128, 128 };
		unlock_cd--;

		

		
		if (unlock_state == 1)
		{
			if (unlock_cd % 4 == 0)
			{
				unlock_pos.x += 2;
			}
			else if (unlock_cd % 4 == 1)
			{
				unlock_pos.x -= 2;
			}
			else if (unlock_cd % 4 == 2)
			{
				unlock_pos.y += 2;
			}
			else if (unlock_cd % 4 == 3)
			{
				unlock_pos.y -= 2;
			}

			app->render->DrawTexture(whitemark_128x128, unlock_pos.x + c_x, unlock_pos.y + c_y, &or);
			app->render->DrawTexture(unknow_tex, unlock_pos.x + c_x, unlock_pos.y + c_y);
		}
		else
		{
			app->render->DrawTexture(whitemark_128x128, unlock_pos.x + c_x, unlock_pos.y + c_y, &or );

			

			object_buttons[0].rect.x = (640 - (object_buttons[0].rect.w / 2) + c_x);
			object_buttons[0].rect.y = unlock_pos.y + 200 + c_y;
			object_buttons[1].rect.x = (640 - (object_buttons[0].rect.w / 2) + c_x);
			object_buttons[1].rect.y = unlock_pos.y + 300 + c_y;

			for (size_t i = 0; i < NUM_OBJECT_BUTTONS; i++)
			{
				if (object_buttons[i].state == 0)
				{
					or = { 0, 0, 500, 70 };
				}
				else if (object_buttons[i].state == 1)
				{
					or = { 0, 70, 500, 70 };
				}
				else if (object_buttons[i].state == 2)
				{
					or = { 0, 140, 500, 70 };
				}

				
				else
				{
					app->render->DrawTexture(whitemark_500x70, object_buttons[i].rect.x, object_buttons[i].rect.y, &or );
				}
			}

			
		}
	}

	return true;
}

// Called before quitting
bool Menu::CleanUp()
{

	return true;
}

bool Menu::GetGameState()
{
	return paused;
}

void Menu::SetWinLoseScape(int n)
{
	if (n == 0)
	{
		if (!win)
		{
			app->audio->PlayFx(win_sound);
		}
		win = true;
		
	}
	else if (n == 1)
	{
		if (!lose)
		{
			app->audio->PlayFx(lose_sound);
		}
		lose = true;
		
	}
	else if (n == 2)
	{
		scape = true;
		
	}
	else
	{
		win = false;
		lose = false;
		scape = false;
	}
}

bool Menu::ReturnStartScreen()
{
	started = false;
	
	return true;
}

void Menu::DisableAll()
{
	
	if (app->scene->Enabled()) { app->scene->Disable(); }
	
}

void Menu::InitPlayer()
{
	if (firstime)
	{
		
		firstime = false;
	}

	// after fadeout
	started = true;
}




bool Menu::InAnyButton()
{

	for (size_t i = 0; i < NUM_PAUSE_BUTTONS; i++)
	{
		if (pause_buttons[i].state == 1)
		{
			return true;
		}
	}
	for (size_t i = 0; i < NUM_SETTINGS_BUTTONS; i++)
	{
		if (settings_buttons[i].state == 1)
		{
			return true;
		}
	}
	if (win_button.state == 1)
	{
		return true;
	}
	for (size_t i = 0; i < NUM_LOSE_BUTTONS; i++)
	{
		if (lose_buttons[i].state == 1)
		{
			return true;
		}
	}
	for (size_t i = 0; i < NUM_SCAPE_BUTTONS; i++)
	{
		if (scape_buttons[i].state == 1)
		{
			return true;
		}
	}
	for (size_t i = 0; i < NUM_OBJECT_BUTTONS; i++)
	{
		if (object_buttons[i].state == 1)
		{
			return true;
		}
	}
	for (size_t i = 0; i < NUM_ASK_BUTTONS; i++)
	{
		if (ask_buttons[i].state == 1)
		{
			return true;
		}
	}

	return false;
}

SDL_Rect Menu::GetUnlockRect(std::string aei)
{
	SDL_Rect res = { -128, 0, 128, 128 };

	if (aei == "999")
	{
		return res;
	}

	if (aei[0] == '0') // assassin
	{
		if (aei[1] == '0') // helmet
		{
			if (aei[2] == '1')
			{
				res = { 0, 0, 128, 128 };
			}
			else if (aei[2] == '2')
			{
				res = { 128, 0, 128, 128 };
			}
			else if (aei[2] == '3')
			{
				res = { 256, 0, 128, 128 };
			}
			else if (aei[2] == '4')
			{
				res = { 384, 0, 128, 128 };
			}
		}
		else if (aei[1] == '1') // chestplate
		{
			if (aei[2] == '1')
			{
				res = { 0, 128, 128, 128 };
			}
			else if (aei[2] == '2')
			{
				res = { 128, 128, 128, 128 };
			}
			else if (aei[2] == '3')
			{
				res = { 256, 128, 128, 128 };
			}
			else if (aei[2] == '4')
			{
				res = { 384, 128, 128, 128 };
			}
		}
		else if (aei[1] == '2') // boots
		{
			if (aei[2] == '1')
			{
				res = { 0, 256, 128, 128 };
			}
			else if (aei[2] == '2')
			{
				res = { 128, 256, 128, 128 };
			}
			else if (aei[2] == '3')
			{
				res = { 256, 256, 128, 128 };
			}
			else if (aei[2] == '4')
			{
				res = { 384, 256, 128, 128 };
			}
		}
		else if (aei[1] == '3') // weapon
		{
			if (aei[2] == '1')
			{
				res = { 0, 384, 128, 128 };
			}
			else if (aei[2] == '2')
			{
				res = { 128, 384, 128, 128 };
			}
			else if (aei[2] == '3')
			{
				res = { 256, 384, 128, 128 };
			}
			else if (aei[2] == '4')
			{
				res = { 384, 384, 128, 128 };
			}
		}
	}
	else if (aei[0] == '1') // healer
	{
		if (aei[1] == '0') // helmet
		{
			if (aei[2] == '1')
			{
				res = { 0, 512, 128, 128 };
			}
			else if (aei[2] == '2')
			{
				res = { 128, 512, 128, 128 };
			}
			else if (aei[2] == '3')
			{
				res = { 256, 512, 128, 128 };
			}
			else if (aei[2] == '4')
			{
				res = { 384, 512, 128, 128 };
			}
		}
		else if (aei[1] == '1') // chestplate
		{
			if (aei[2] == '1')
			{
				res = { 0, 640, 128, 128 };
			}
			else if (aei[2] == '2')
			{
				res = { 128, 640, 128, 128 };
			}
			else if (aei[2] == '3')
			{
				res = { 256, 640, 128, 128 };
			}
			else if (aei[2] == '4')
			{
				res = { 384, 640, 128, 128 };
			}
		}
		else if (aei[1] == '2') // boots
		{
			if (aei[2] == '1')
			{
				res = { 0, 768, 128, 128 };
			}
			else if (aei[2] == '2')
			{
				res = { 128, 768, 128, 128 };
			}
			else if (aei[2] == '3')
			{
				res = { 256, 768, 128, 128 };
			}
			else if (aei[2] == '4')
			{
				res = { 384, 768, 128, 128 };
			}
		}
		else if (aei[1] == '3') // weapon
		{
			if (aei[2] == '1')
			{
				res = { 0, 896, 128, 128 };
			}
			else if (aei[2] == '2')
			{
				res = { 128, 896, 128, 128 };
			}
			else if (aei[2] == '3')
			{
				res = { 256, 896, 128, 128 };
			}
			else if (aei[2] == '4')
			{
				res = { 384, 896, 128, 128 };
			}
		}
	}
	else if (aei[0] == '2') // tank
	{
		if (aei[1] == '0') // helmet
		{
			if (aei[2] == '1')
			{
				res = { 0, 1024, 128, 128 };
			}
			else if (aei[2] == '2')
			{
				res = { 128, 1024, 128, 128 };
			}
			else if (aei[2] == '3')
			{
				res = { 256, 1024, 128, 128 };
			}
			else if (aei[2] == '4')
			{
				res = { 384, 1024, 128, 128 };
			}
		}
		else if (aei[1] == '1') // chestplate
		{
			if (aei[2] == '1')
			{
				res = { 0, 1152, 128, 128 };
			}
			else if (aei[2] == '2')
			{
				res = { 128, 1152, 128, 128 };
			}
			else if (aei[2] == '3')
			{
				res = { 256, 1152, 128, 128 };
			}
			else if (aei[2] == '4')
			{
				res = { 384, 1152, 128, 128 };
			}
		}
		else if (aei[1] == '2') // boots
		{
			if (aei[2] == '1')
			{
				res = { 0, 1280, 128, 128 };
			}
			else if (aei[2] == '2')
			{
				res = { 128, 1280, 128, 128 };
			}
			else if (aei[2] == '3')
			{
				res = { 256, 1280, 128, 128 };
			}
			else if (aei[2] == '4')
			{
				res = { 384, 1280, 128, 128 };
			}
		}
		else if (aei[1] == '3') // weapon
		{
			if (aei[2] == '1')
			{
				res = { 0, 1408, 128, 128 };
			}
			else if (aei[2] == '2')
			{
				res = { 128, 1408, 128, 128 };
			}
			else if (aei[2] == '3')
			{
				res = { 256, 1408, 128, 128 };
			}
			else if (aei[2] == '4')
			{
				res = { 384, 1408, 128, 128 };
			}
		}
	}
	else if (aei[0] == '3') // wizard
	{
		if (aei[1] == '0') // helmet
		{
			if (aei[2] == '1')
			{
				res = { 0, 1536, 128, 128 };
			}
			else if (aei[2] == '2')
			{
				res = { 128, 1536, 128, 128 };
			}
			else if (aei[2] == '3')
			{
				res = { 256, 1536, 128, 128 };
			}
			else if (aei[2] == '4')
			{
				res = { 384, 1536, 128, 128 };
			}
		}
		else if (aei[1] == '1') // chestplate
		{
			if (aei[2] == '1')
			{
				res = { 0, 1664, 128, 128 };
			}
			else if (aei[2] == '2')
			{
				res = { 128, 1664, 128, 128 };
			}
			else if (aei[2] == '3')
			{
				res = { 256, 1664, 128, 128 };
			}
			else if (aei[2] == '4')
			{
				res = { 384, 1664, 128, 128 };
			}
		}
		else if (aei[1] == '2') // boots
		{
			if (aei[2] == '1')
			{
				res = { 0, 1792, 128, 128 };
			}
			else if (aei[2] == '2')
			{
				res = { 128, 1792, 128, 128 };
			}
			else if (aei[2] == '3')
			{
				res = { 256, 1792, 128, 128 };
			}
			else if (aei[2] == '4')
			{
				res = { 384, 1792, 128, 128 };
			}
		}
		else if (aei[1] == '3') // weapon
		{
			if (aei[2] == '1')
			{
				res = { 0, 1920, 128, 128 };
			}
			else if (aei[2] == '2')
			{
				res = { 128, 1920, 128, 128 };
			}
			else if (aei[2] == '3')
			{
				res = { 256, 1920, 128, 128 };
			}
			else if (aei[2] == '4')
			{
				res = { 384, 1920, 128, 128 };
			}
		}
	}
	else if (aei[0] == '4') // items
	{
		switch (aei[1])
		{
		case '0': res = { 256, 0, 128, 128 }; break;
		case '1': res = { 384, 0, 128, 128 }; break;
		case '2': res = { 512, 0, 128, 128 }; break;
		case '3': res = { 0, 128, 128, 128 }; break;
		case '4': res = { 128, 128, 128, 128 }; break;
		case '5': res = { 256, 128, 128, 128 }; break;
		case '6': res = { 384, 128, 128, 128 }; break;
		case '7': res = { 512, 128, 128, 128 }; break;
		}
	}
	else if (aei[0] == '5') // items
	{
		switch (aei[1])
		{
		case '0': res = { 128, 256, 128, 128 }; break;
		case '1': res = { 256, 256, 128, 128 }; break;
		case '2': res = { 384, 256, 128, 128 }; break;
		case '3': res = { 512, 256, 128, 128 }; break;
		}
	}

	return res;
}