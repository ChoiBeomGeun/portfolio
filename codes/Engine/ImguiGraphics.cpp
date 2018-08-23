/******************************************************************************/
/*!
\file   ImguiGraphics.cpp
\author Choi Beom Geun
\par    email: o77151@gmail.com
\par    Class:GAM250
\par    ThumbUp Engine
\date   2017/11/29

Imgui drawing source file
All content 2018 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "ImguiGraphics.h"
#include "StateManager.h"
#include "SoundManager.h"
bool IsImguiOn = false;
using namespace TE;
char** cppLevelitems;
char** cppTextureitems;
char** cppSounditems;
char** cppArchetypesditems;
bool Soundnew = true;
bool textnew = true;
bool Leveldnew = true;
bool Archetynew = true;
static int j = -1;

void ImGuiUpdate(void) {


	ImGui_ImplSdlGL3_NewFrame(APP->pWnd);
	if (Input::IsTriggered(SDL_SCANCODE_F5))
	{
		IsImguiOn = true;


	}
	if (IsImguiOn)
	{
		static int vec4f[2] = { 800, 600 };
		static int vec4i[4] = { 1, 5, 100, 255 };




		if (ImGui::CollapsingHeader("SoundManager"))
		{
			static int t = -1;
			if (Soundnew) {
				cppSounditems = new char*[ENGINE->mVsSoundnamelist.size() + 1];
				Soundnew = false;
			}
			for (unsigned int i = 0; i < ENGINE->mVsSoundnamelist.size(); i++)
			{
				cppSounditems[i] = const_cast<char*>(ENGINE->mVsSoundnamelist[i].c_str());

			}
			ImGui::Combo("Sounds", &t, cppSounditems, (int)ENGINE->mVsSoundnamelist.size());
			if (ImGui::Button("Play"))
			{
				SOUNDID temp = SOUNDMANAGER->LoadSound(cppSounditems[t]);
				SOUNDMANAGER->PlaySounds(temp, false);

			}
			if (ImGui::Button("Mute"))
				SOUNDMANAGER->PauseAllSound();
			if (ImGui::Button("Unmute"))
				SOUNDMANAGER->ResumeAllSound();



		}
		std::string test = "Object";

		if (ImGui::CollapsingHeader("CameraManager"))
		{
			ImGui::SliderFloat("CAMERAEYEx", &CAMERA->cameraPos.x, -5000, 5000);
			ImGui::SliderFloat("CAMERAEYEy", &CAMERA->cameraPos.y, -5000, 5000);
			ImGui::SliderFloat("CAMERAEYEz", &CAMERA->cameraPos.z, 0, 999);

			ImGui::SliderFloat("CAMERATRAGETx", &CAMERA->cameraTarget.x, -50, 50);
			ImGui::SliderFloat("CAMERATRAGETy", &CAMERA->cameraTarget.y, -50, 50);
			ImGui::SliderFloat("CAMERATRAGETz", &CAMERA->cameraTarget.z, -50, 50);

			ImGui::SliderFloat("CAMERAUPx", &CAMERA->cameraUp.x, -50, 50);
			ImGui::SliderFloat("CAMERAUPy", &CAMERA->cameraUp.y, -50, 50);
			ImGui::SliderFloat("CAMERAUPz", &CAMERA->cameraUp.z, -50, 50);

		}

		if (ImGui::CollapsingHeader("ObjectManager"))
		{
			ImGui::Indent();
			std::string ObjectStyle;
			for (auto i : FACTORY->ObjectIDMap)
			{
				switch (i.second->objectstyle)
				{
				case Objectstyle::Clearzone:
					ObjectStyle = "Clearzone";
					break;
				case Objectstyle::Trigger180:
					ObjectStyle = "Trigger180";
					break;
				case Objectstyle::Trigger90:
					ObjectStyle = "Trigger90";
					break;
				case Objectstyle::Button:
					ObjectStyle = "Button";
					break;
				case Objectstyle::Player:
					ObjectStyle = "Player";
					break;
				case Objectstyle::Wall:
					ObjectStyle = "Wall";
					break;
				case Objectstyle::Box:
					ObjectStyle = "Box";
					break;
				case Objectstyle::Particle:
					ObjectStyle = "Particle";
					break;
				case Objectstyle::BackGround:
					ObjectStyle = "BackGround";
					break;
				case Objectstyle::Hazard:
					ObjectStyle = "Hazard";
					break;
				}
				std::string Object = "Object" + std::to_string(i.second->objID) + " - ";
				std::string ObjectScale = "Scale";
				std::string ObjectPosition = "Position";
				std::string ObjectVelocity = "Velocity";
				std::string ObjectRotation = "Rotation";
				std::string ObjectMass = "Mass";

				Object += ObjectStyle;

				ObjectScale += std::to_string(i.second->objID);
				ObjectPosition += std::to_string(i.second->objID);
				if (ImGui::CollapsingHeader(Object.c_str()))
				{
					if (i.second->objectstyle != Objectstyle::Player &&
						i.second->objectstyle != Objectstyle::Clearzone) {
						if (ImGui::Button(("Delete" + Object).c_str()))
						{
							FACTORY->Destroy(i.second);

						}
					}
					// Transform Component
					if (FACTORY->ObjectIDMap[i.first]->HasComponent<Transform>())
					{
						if (ImGui::TreeNode(("Transform " + std::to_string(i.second->objID)).c_str()))
						{

							ImGui::SliderFloat((ObjectScale + "x").c_str(), &FACTORY->ObjectIDMap[i.first]->GetComponent<Transform>()->scale.x, 0, (float)APP->_screenWidth);
							ImGui::SliderFloat((ObjectScale + "y").c_str(), &FACTORY->ObjectIDMap[i.first]->GetComponent<Transform>()->scale.y, 0, (float)APP->_screenHeight);
							ImGui::SliderFloat((ObjectScale + "z").c_str(), &FACTORY->ObjectIDMap[i.first]->GetComponent<Transform>()->scale.z, 0, 1);
							ImGui::SliderFloat((ObjectPosition + "x").c_str(), &FACTORY->ObjectIDMap[i.first]->GetComponent<Transform>()->position.x, -1000.f, 1000.f);
							ImGui::SliderFloat((ObjectPosition + "y").c_str(), &FACTORY->ObjectIDMap[i.first]->GetComponent<Transform>()->position.y, -1000.f, 1000.f);
							ImGui::SliderFloat((ObjectPosition + "z").c_str(), &FACTORY->ObjectIDMap[i.first]->GetComponent<Transform>()->position.z, -1000.f, 1000.f);
							ImGui::SliderFloat((ObjectRotation + "z").c_str(), &FACTORY->ObjectIDMap[i.first]->GetComponent<Transform>()->angle, 0, TUMath::PI);

							ImGui::TreePop();
						}
					}
					if (FACTORY->ObjectIDMap[i.first]->HasComponent<Body>())
					{

						if (ImGui::TreeNode(("Body " + std::to_string(i.second->objID)).c_str()))
						{
							ImGui::SliderFloat((ObjectVelocity + "x").c_str(), &FACTORY->ObjectIDMap[i.first]->GetComponent<Body>()->pm_velocity.x, -1000.f, 1000.f);
							ImGui::SliderFloat((ObjectVelocity + "y").c_str(), &FACTORY->ObjectIDMap[i.first]->GetComponent<Body>()->pm_velocity.y, -1000.f, 1000.f);
							ImGui::SliderFloat(ObjectMass.c_str(), &FACTORY->ObjectIDMap[i.first]->GetComponent<Body>()->pm_mass, 0, (float)APP->_screenHeight);
							ImGui::TreePop();
						}
					}
					if (FACTORY->ObjectIDMap[i.first]->HasComponent<Sprite>())
					{

						if (ImGui::TreeNode(("Sprite " + std::to_string(i.second->objID)).c_str()))
						{
							int arraysize2 = 0;
							if (textnew) {
								cppTextureitems = new char*[ENGINE->mVsTexturenamelist.size() + 1];
								textnew = false;
							}
							for (unsigned int j = 0; j < ENGINE->mVsTexturenamelist.size(); j++)
							{
								cppTextureitems[j] = const_cast<char*>(ENGINE->mVsTexturenamelist[j].c_str());
								arraysize2 = j;
							}

							ImGui::Combo("Levels", &j, cppTextureitems, (int)ENGINE->mVsTexturenamelist.size());
							if (ImGui::Button("Load"))
							{
								i.second->GetComponent<Sprite>()->m_TextureID = Sprite::find_texture_id(cppTextureitems[j]);
								i.second->GetComponent<Sprite>()->mTexutureDir = cppTextureitems[j];
							}
							ImGui::ColorEdit4("Color", FACTORY->ObjectIDMap[i.second->objID]->GetComponent<Sprite>()->Color, ImGuiColorEditFlags_Uint8);
							ImGui::SliderFloat("Depth", &FACTORY->ObjectIDMap[i.second->objID]->GetComponent<Sprite>()->depth, -10, 10);

							ImGui::TreePop();
						}
					}
					if (FACTORY->ObjectIDMap[i.first]->HasComponent<Emitter>())
					{
						std::string EmitterOn = "EmitterOn";
						std::string lifeTime = "lifeTime";
						std::string particleVel = "vel";
						std::string particleScl = "scale";
						if (ImGui::TreeNode(("Particle " + std::to_string(i.second->objID)).c_str()))
						{

							ImGui::SliderFloat((ObjectPosition + "x").c_str(), &FACTORY->ObjectIDMap[i.first]->GetComponent<Emitter>()->pos.x, -1000.f, 1000.f);
							ImGui::SliderFloat((ObjectPosition + "y").c_str(), &FACTORY->ObjectIDMap[i.first]->GetComponent<Emitter>()->pos.y, -1000.f, 1000.f);
							ImGui::SliderFloat((ObjectPosition + "z").c_str(), &FACTORY->ObjectIDMap[i.first]->GetComponent<Emitter>()->pos.z, -1000.f, 1000.f);

							ImGui::SliderFloat((particleVel + "x").c_str(), &PARTICLEMANAGER->m_laserVel.x, -100, 100.f);
							ImGui::SliderFloat((particleVel + "y").c_str(), &PARTICLEMANAGER->m_laserVel.y, -100, 100.f);

							ImGui::SliderFloat((particleScl + "min").c_str(), &PARTICLEMANAGER->m_minTrailScale, -100, 100);
							ImGui::SliderFloat((particleScl + "max").c_str(), &PARTICLEMANAGER->m_maxTrailScale, -100, 100);




							ImGui::Text("Particle Type is %s", &FACTORY->ObjectIDMap[i.first]->GetComponent<Emitter>()->type);
							ImGui::Checkbox(EmitterOn.c_str(), &FACTORY->ObjectIDMap[i.first]->GetComponent<Emitter>()->isOn);

							ImGui::SliderFloat(lifeTime.c_str(), &FACTORY->ObjectIDMap[i.first]->GetComponent<Emitter>()->explifeTime, 0.f, 50.f);

							ImGui::TreePop();
						}
					}

				}
			}
			static int t = -1;
			if (Archetynew) {
				cppArchetypesditems = new char*[ENGINE->mVsArchtypenamelist.size() + 1];
				Archetynew = false;


			}
			for (unsigned int i = 0; i < ENGINE->mVsArchtypenamelist.size(); i++)
			{
				cppArchetypesditems[i] = const_cast<char*>(ENGINE->mVsArchtypenamelist[i].c_str());

			}

			ImGui::Combo("Archtypes", &t, cppArchetypesditems, (int)ENGINE->mVsArchtypenamelist.size());


			if (ImGui::Button("Make Archtypes"))
				FACTORY->CreateArchetype(ReadingArchetype(cppArchetypesditems[t]));

		}
		if (Leveldnew) {
			cppLevelitems = new char*[ENGINE->mVsLevelnamelist.size() + 1];
			Leveldnew = false;
		}
		for (unsigned int i = 0; i < ENGINE->mVsLevelnamelist.size(); i++)
		{
			cppLevelitems[i] = const_cast<char*>(ENGINE->mVsLevelnamelist[i].c_str());

		}
		static int t = -1;

		if (ImGui::CollapsingHeader("Levels"))
		{
			ImGui::Combo("Levels", &t, cppLevelitems, (int)ENGINE->mVsLevelnamelist.size());
			if (ImGui::Button("Save"))
				LEVELMANAGER->SaveLevel(cppLevelitems[t]);
			ImGui::SameLine();
			if (ImGui::Button("Load")) {
				STATEMANAGER->forceLevelLoading = true;
				LEVELMANAGER->LoadLevel(cppLevelitems[t]);
			}
		}


		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::Text("Object Number : %d", FACTORY->GetAllObjectNumbers());
		if (ImGui::Button("RefreshFileLists"))
			ENGINE->Filenameloading();
	}




	ImGui::Render();

}





void ImguiFree(void)
{

	delete cppTextureitems;
	delete cppLevelitems;

	delete cppSounditems;
	delete cppArchetypesditems;

}