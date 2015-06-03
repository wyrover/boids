//
//  UILevelChooseLayer.h
//  Boids
//
//  Created by Yanjie Chen on 3/3/15.
//
//

#ifndef __Boids__UILevelChooseLayer__
#define __Boids__UILevelChooseLayer__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "MapData.h"
#include "TouchableLayer.h"

typedef enum {
    LevelDiffEasy = 1,
    LevelDiffMedium = 2,
    LevelDiffHard = 3
}eLevelDifficulty;

class UILevelChooseLayer : public TouchableLayer {
private:
    cocos2d::Node* _main_node;
    cocos2d::Node* _level_node;
    
    cocos2d::ui::ScrollView* _scrollview;
    cocos2d::Sprite* _background_node;
    cocos2d::ui::Button* _back_button;
    cocos2d::ui::Button* _start_button;
    std::vector<cocos2d::ui::Text*> _mission_labels;
    cocos2d::ui::Text* _level_info_label;
    
    MapData* _map_data;
    bool _is_pvp;
    rapidjson::Document _level_logic;
    
    eLevelDifficulty _difficulty;
    
    cocostudio::timeline::ActionTimeline* _panel_action;
    
    cocos2d::ui::Text* _lb_player_name;
    
public:
    UILevelChooseLayer();
    ~UILevelChooseLayer();
    
    static UILevelChooseLayer* create();
    
    virtual bool init();
    
    void onStartButtonTouched( cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type );
    void onBackButtonTouched( cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type );
    void onLevelTouched( cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type );
    
    void onStoreTouched( cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type );
    void onHeroTouched( cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type );
    void onTeamSkillTouched( cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type );
    
    eLevelDifficulty getDifficulty();
    void setDifficulty( eLevelDifficulty diff );
    void onDifficultyTouched( cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type );
    
    void setMapData( MapData* map_data );
    
    void loadDeployedHeros();
    
    virtual void becomeTopLayer();
};

#endif /* defined(__Boids__UILevelChooseLayer__) */
