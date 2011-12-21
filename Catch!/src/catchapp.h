#ifndef _catchapp_h
#define _catchapp_h

#include "levelzones.h"
#include "levelloader.h"
#include "levelscorer.h"
#include <mezzanine.h>

using namespace Mezzanine;

class CatchApp
{
    public:
        enum GameState
        {
            Catch_Init,
            Catch_Loading,
            Catch_MenuScreen,
            Catch_GameScreen,
            Catch_Paused
        };
    protected:
        static CatchApp* TheRealCatchApp;
        const Plane PlaneOfPlay;
        World* TheWorld;
        LevelLoader* Loader;
        LevelScorer* Scorer;
        ActorBase* LastActorThrown;
        Whole CurrScore;
        CatchApp::GameState CurrentState;
        std::vector<ActorBase*> ThrownItems;
        std::vector<StartArea*> StartAreas;
        std::vector<ScoreArea*> ScoreAreas;

        SimpleTimer* LevelTimer;
        SimpleTimer* EndTimer;

        void MakeGUI();
        void CreateLoadingScreen();
        void ConfigResources();
        void InitMusic();

        void PopulateLevelList(UI::PagedCellGrid* Grid);
        void ChangeState(const CatchApp::GameState &StateToSet);

        bool CheckEndOfLevel();
        bool AllStartZonesEmpty();
        bool IsInsideAnyStartZone(ActorBase* Actor);
        void UnloadLevel();
    public:
        CatchApp();
        ~CatchApp();

        static CatchApp* GetCatchAppPointer();
        int GetCatchin();

        //Callbacks AKA Functions the mainloops call
        bool PreInput();
        bool PostInput();
        bool PreUI();
        bool PostUI();
        bool PrePhysics();
        bool PostPhysics();
        bool PostRender();

        bool CheckForStuff();
        bool IsAThrowable(ActorBase* Actor);
        void RegisterScoreArea(ScoreArea* Score);
        void RegisterStartArea(StartArea* Start);
        void AddThrowable(ActorBase* Throwable);
        LevelLoader* GetLevelLoader();
        SimpleTimer* GetLevelTimer();
        SimpleTimer* GetEndTimer();
};

#endif
