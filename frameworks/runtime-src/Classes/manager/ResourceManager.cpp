//
//  ResourceManager.cpp
//  Boids
//
//  Created by Yanjie Chen on 3/2/15.
//
//

#include "ResourceManager.h"
#include "../constant/BoidsConstant.h"
#include "../Utils.h"
#include "../ArmatureManager.h"
#include "cocostudio/CocoStudio.h"
#include "../data/PlayerInfo.h"
#include "external/json/document.h"
#include "../util/CocosUtils.h"

#define EQUIP_CONFIG_FILE "equip"
#define TALENT_CONFIG_FILE "talent"
#define BULLET_CONFIG_FILE "bullet"
#define ITEM_CONFIG_FILE "item"
#define LEVEL_CONFIG_FILE "level"
#define PLAYER_INFO_CONFIG_FILE "player_info"
#define SKILL_CONFIG_FILE "skill_conf"
#define SKILL_UPGRADE_COST_CONFIG_FILE "skill_upgrade_cost"
#define TEAM_LEVEL_EXP_CONFIG_FILE "team_level_exp"
#define TEAM_SKILL_EXP_CONFIG_FILE "team_skill_exp_conf"
#define TOWER_CONFIG_FILE "tower"
#define UNIT_CONFIG_FILE "unit"
#define UPGRADE_COST_CONFIG_FILE "upgrade_cost"
#define DROP_CONFIG_FILE "drop"

using namespace cocos2d;

ResourceManager* ResourceManager::_instance = nullptr;

ResourceManager::ResourceManager() {
    
}

ResourceManager::~ResourceManager() {
    
}

ResourceManager* ResourceManager::getInstance() {
    if( _instance == nullptr ) {
        _instance = new ResourceManager();
    }
    return _instance;
}

void ResourceManager::destroy() {
    if( _instance ) {
        delete _instance;
        _instance = nullptr;
    }
}

void ResourceManager::loadMap( MapData* map_data ) {
    const ValueMap& meta_json = map_data->getMetaJson();
    
    const ValueVector& unit_names = meta_json.at( "units" ).asValueVector();
    this->loadUnitArmatures( unit_names );
    
    const ValueVector& player_unit_names = PlayerInfo::getInstance()->getPlayerDeployedUnitNames();
    this->loadUnitArmatures( player_unit_names );
}

void ResourceManager::purgeMap( MapData* map_data ) {
    const ValueMap& meta_json = map_data->getMetaJson();
    
    const ValueVector& unit_names = meta_json.at( "units" ).asValueVector();
    this->purgeUnitArmatures( unit_names );
    
    const ValueVector& player_unit_names = PlayerInfo::getInstance()->getPlayerDeployedUnitNames();
    this->purgeUnitArmatures( player_unit_names );
}

void ResourceManager::loadAllData() {
    this->loadDefaultData();
    this->loadGameConfig();
    this->loadUnitData();
    this->loadTalentData();
    this->loadEquipData();
    this->loadTowerData();
    this->loadUnitLevelupCostData();
    this->loadBulletData();
    this->loadCenterData();
//    this->loadBuildingData();
    this->loadBattleUIData();
    this->loadLevelData();
    this->loadSkillData();
    this->loadSkillUpgradeCostData();
    this->loadTeamLevelExpData();
    this->loadDropData();
}

void ResourceManager::loadDefaultData() {
}

void ResourceManager::unloadDefaultData() {
    SpriteFrameCache* frame_cache = SpriteFrameCache::getInstance();
    frame_cache->removeSpriteFrames();
    Director::getInstance()->getTextureCache()->removeAllTextures();
//    frame_cache->removeUnusedSpriteFrames();
}

void ResourceManager::loadOpenningResource() {
    SpriteFrameCache* frame_cache = SpriteFrameCache::getInstance();
    frame_cache->addSpriteFramesWithFile( "ui/page/ui_movie1.plist", "ui/page/ui_movie1.png"  );
    frame_cache->addSpriteFramesWithFile( "ui/page/ui_movie2.plist", "ui/page/ui_movie2.png"  );
    frame_cache->addSpriteFramesWithFile( "ui/page/ui_movie3.plist", "ui/page/ui_movie3.png"  );
    frame_cache->addSpriteFramesWithFile( "ui/page/ui_movie4.plist", "ui/page/ui_movie4.png"  );
    frame_cache->addSpriteFramesWithFile( "ui/page/ui_movie5.plist", "ui/page/ui_movie5.png"  );
    frame_cache->addSpriteFramesWithFile( "ui/page/ui_movie67.plist", "ui/page/ui_movie67.png"  );
    frame_cache->addSpriteFramesWithFile( "ui/page/ui_movie8.plist", "ui/page/ui_movie8.png"  );
}

void ResourceManager::unloadOpenningResource() {
    SpriteFrameCache* frame_cache = SpriteFrameCache::getInstance();
    frame_cache->removeSpriteFramesFromFile( "ui/page/ui_movie1.plist" );
    frame_cache->removeSpriteFramesFromFile( "ui/page/ui_movie2.plist" );
    frame_cache->removeSpriteFramesFromFile( "ui/page/ui_movie3.plist" );
    frame_cache->removeSpriteFramesFromFile( "ui/page/ui_movie4.plist" );
    frame_cache->removeSpriteFramesFromFile( "ui/page/ui_movie5.plist" );
    frame_cache->removeSpriteFramesFromFile( "ui/page/ui_movie6.plist" );
    frame_cache->removeSpriteFramesFromFile( "ui/page/ui_movie7.plist" );
}

void ResourceManager::loadUIResource() {
    SpriteFrameCache* frame_cache = SpriteFrameCache::getInstance();
    frame_cache->addSpriteFramesWithFile( "ui/page/ui_common.plist", "ui/page/ui_common.png"  );
    frame_cache->addSpriteFramesWithFile( "ui/page/ui_win_lose_page.plist", "ui/page/ui_win_lose_page.png"  );
    frame_cache->addSpriteFramesWithFile( "ui/page/ui_battle.plist", "ui/page/ui_battle.png"  );
//    frame_cache->addSpriteFramesWithFile( "ui/page/ui_popup.plist", "ui/page/ui_popup.png"  );
    frame_cache->addSpriteFramesWithFile( "ui/page/ui_hero_detail.plist", "ui/page/ui_hero_detail.png"  );
    frame_cache->addSpriteFramesWithFile( "ui/page/ui_hero_manage.plist", "ui/page/ui_hero_manage.png" );
    frame_cache->addSpriteFramesWithFile( "ui/page/ui_home.plist", "ui/page/ui_home.png"  );
    frame_cache->addSpriteFramesWithFile( "ui/page/ui_talent.plist", "ui/page/ui_talent.png" );
    frame_cache->addSpriteFramesWithFile( "ui/page/ui_skill_icon.plist", "ui/page/ui_skill_icon.png" );
    frame_cache->addSpriteFramesWithFile( "ui/ui_hero_p.plist", "ui/ui_hero_p.png" );
    frame_cache->addSpriteFramesWithFile( "ui/ui_hero_f.plist", "ui/ui_hero_f.png" );
    frame_cache->addSpriteFramesWithFile( "ui/ui_equip_icon.plist", "ui/ui_equip_icon.png" );
    frame_cache->addSpriteFramesWithFile( "ui/map_common.plist", "ui/map_common.png" );
    frame_cache->addSpriteFramesWithFile( "ui/ui_battle_hint.plist", "ui_battle_hint.png" );
}

void ResourceManager::unloadUIResource() {
    SpriteFrameCache* frame_cache = SpriteFrameCache::getInstance();
    frame_cache->removeSpriteFramesFromFile( "ui/page/ui_common.plist" );
    frame_cache->removeSpriteFramesFromFile( "ui/page/ui_win_lose_page.plist" );
    frame_cache->removeSpriteFramesFromFile( "ui/page/ui_battle.plist" );
    frame_cache->removeSpriteFramesFromFile( "ui/page/ui_hero_detail.plist" );
    frame_cache->removeSpriteFramesFromFile( "ui/page/ui_hero_manage.plist" );
    frame_cache->removeSpriteFramesFromFile( "ui/page/ui_home.plist" );
    frame_cache->removeSpriteFramesFromFile( "ui/page/ui_talent.plist" );
    frame_cache->removeSpriteFramesFromFile( "ui/page/ui_skill_icon.plist" );
    frame_cache->removeSpriteFramesFromFile( "ui/ui_hero_p.plist" );
    frame_cache->removeSpriteFramesFromFile( "ui/ui_hero_f.plist" );
    frame_cache->removeSpriteFramesFromFile( "ui/ui_equip_icon.plist" );
    frame_cache->removeSpriteFramesFromFile( "ui/map_common.plist" );
    frame_cache->removeSpriteFramesFromFile( "ui/ui_battle_hint.plist" );
}

void ResourceManager::loadBattleResource() {
    SpriteFrameCache* frame_cache = SpriteFrameCache::getInstance();
    frame_cache->addSpriteFramesWithFile( "ui/ui_battle_hint.plist", "ui/ui_battle_hint.png"  );
    frame_cache->addSpriteFramesWithFile( "ui/page/ui_win_lose_page.plist", "ui/page/ui_win_lose_page.png"  );
    frame_cache->addSpriteFramesWithFile( "ui/page/ui_common.plist", "ui/page/ui_common.png"  );
    frame_cache->addSpriteFramesWithFile( "ui/page/ui_pause.plist", "ui/page/ui_pause.png" );
    frame_cache->addSpriteFramesWithFile( "ui/page/ui_battle.plist", "ui/page/ui_battle.png"  );
    frame_cache->addSpriteFramesWithFile( "ui/ui_equip_icon.plist", "ui/ui_equip_icon.png" );
    frame_cache->addSpriteFramesWithFile( "ui/ui_equip_drop.plist", "ui/ui_equip_drop.png" );
    frame_cache->addSpriteFramesWithFile( "maps/map_images/base_terrain.plist", "maps/map_images/base_terrain.png" );
    frame_cache->addSpriteFramesWithFile( "maps/map_images/building_1.plist", "maps/map_images/building_1.png" );
    frame_cache->addSpriteFramesWithFile( "maps/map_images/building_2.plist", "maps/map_images/building_2.png" );
    frame_cache->addSpriteFramesWithFile( "maps/map_images/building_3.plist", "maps/map_images/building_3.png" );
    frame_cache->addSpriteFramesWithFile( "maps/map_images/building_4.plist", "maps/map_images/building_4.png" );
    frame_cache->addSpriteFramesWithFile( "maps/map_images/decoration_1.plist", "maps/map_images/decoration_1.png" );
    frame_cache->addSpriteFramesWithFile( "maps/map_images/decoration_2.plist", "maps/map_images/decoration_2.png" );
    frame_cache->addSpriteFramesWithFile( "maps/map_images/decoration_3.plist", "maps/map_images/decoration_3.png" );
    frame_cache->addSpriteFramesWithFile( "maps/map_images/obstacle_1.plist", "maps/map_images/obstacle_1.png" );
    frame_cache->addSpriteFramesWithFile( "maps/map_images/terrain_0.plist", "maps/map_images/terrain_0.png" );
    frame_cache->addSpriteFramesWithFile( "maps/map_images/terrain_1.plist", "maps/map_images/terrain_1.png" );
    frame_cache->addSpriteFramesWithFile( "maps/map_images/terrain_2.plist", "maps/map_images/terrain_2.png" );
    frame_cache->addSpriteFramesWithFile( "maps/map_images/terrain_3.plist", "maps/map_images/terrain_3.png" );
    frame_cache->addSpriteFramesWithFile( "maps/map_images/towers.plist", "maps/map_images/towers.png" );
    frame_cache->addSpriteFramesWithFile( "ui/map_common.plist", "ui/map_common.png" );
    frame_cache->addSpriteFramesWithFile( "ui/hero_avatars.plist", "ui/hero_avatars.png" );
    frame_cache->addSpriteFramesWithFile( "ui/ui_boss_avatar.plist", "ui/ui_boss_avatar.png" );
    frame_cache->addSpriteFramesWithFile( "effects/bullets/bullets.plist", "effects/bullets/bullets.png" );
    frame_cache->addSpriteFramesWithFile( "effects/fx_unit_common.plist", "effects/fx_unit_common.png" );
}

void ResourceManager::unloadBattleResource() {
    SpriteFrameCache* frame_cache = SpriteFrameCache::getInstance();
    frame_cache->removeSpriteFramesFromFile( "ui/ui_battle_hint.plist" );
    frame_cache->removeSpriteFramesFromFile( "ui/page/ui_win_lose_page.plist" );
    frame_cache->removeSpriteFramesFromFile( "ui/page/ui_common.plist" );
    frame_cache->removeSpriteFramesFromFile( "ui/page/ui_pause.plist" );
    frame_cache->removeSpriteFramesFromFile( "ui/ui_equip_drop.plist" );
    frame_cache->removeSpriteFramesFromFile( "ui/ui_equip_icon.plist" );
    frame_cache->removeSpriteFramesFromFile( "maps/map_images/base_terrain.plist" );
    frame_cache->removeSpriteFramesFromFile( "maps/map_images/building_1.plist" );
    frame_cache->removeSpriteFramesFromFile( "maps/map_images/building_2.plist" );
    frame_cache->removeSpriteFramesFromFile( "maps/map_images/building_3.plist" );
    frame_cache->removeSpriteFramesFromFile( "maps/map_images/building_4.plist" );
    frame_cache->removeSpriteFramesFromFile( "maps/map_images/decoration_1.plist" );
    frame_cache->removeSpriteFramesFromFile( "maps/map_images/decoration_2.plist" );
    frame_cache->removeSpriteFramesFromFile( "maps/map_images/decoration_3.plist" );
    frame_cache->removeSpriteFramesFromFile( "maps/map_images/obstacle_1.plist" );
    frame_cache->removeSpriteFramesFromFile( "maps/map_images/terrain_0.plist" );
    frame_cache->removeSpriteFramesFromFile( "maps/map_images/terrain_1.plist" );
    frame_cache->removeSpriteFramesFromFile( "maps/map_images/terrain_2.plist" );
    frame_cache->removeSpriteFramesFromFile( "maps/map_images/terrain_3.plist" );
    frame_cache->removeSpriteFramesFromFile( "maps/map_images/towers.plist" );
    frame_cache->removeSpriteFramesFromFile( "ui/map_common.plist" );
    frame_cache->removeSpriteFramesFromFile( "ui/hero_avatars.plist" );
    frame_cache->removeSpriteFramesFromFile( "ui/ui_boss_avatar.plist" );
    frame_cache->removeSpriteFramesFromFile( "effects/bullets/bullets.plist" );
    frame_cache->removeSpriteFramesFromFile( "effects/fx_unit_common.plist" );
}

void ResourceManager::loadGameConfig() {
    FileUtils* file_util = FileUtils::getInstance();
    std::string data_string = file_util->getStringFromFile( "config.json" );
    rapidjson::Document config_json;
    config_json.Parse<0>( data_string.c_str() );
    _game_config = CocosUtils::jsonObjectToValueMap( config_json );
}

void ResourceManager::loadUnitData() {
    FileUtils* file_util = FileUtils::getInstance();
    std::string data_string = file_util->getStringFromFile( "unit.json" );
    rapidjson::Document unit_config_json;
    unit_config_json.Parse<0>( data_string.c_str() );
    _unit_config = CocosUtils::jsonObjectToValueMap( unit_config_json );
}

void ResourceManager::loadTalentData() {
    FileUtils* file_util = FileUtils::getInstance();
    std::string data_string = file_util->getStringFromFile( "talent.json" );
    rapidjson::Document config_json;
    config_json.Parse<0>( data_string.c_str() );
    _talent_config = CocosUtils::jsonObjectToValueMap( config_json );
}

void ResourceManager::loadEquipData() {
    FileUtils* file_util = FileUtils::getInstance();
    std::string data_string = file_util->getStringFromFile( "equip.json" );
    rapidjson::Document equip_config_json;
    equip_config_json.Parse<0>( data_string.c_str() );
    _equip_config = CocosUtils::jsonObjectToValueMap( equip_config_json );
}

void ResourceManager::loadTowerData() {
    FileUtils* file_util = FileUtils::getInstance();
    std::string data_string = file_util->getStringFromFile( "tower.json" );
    rapidjson::Document tower_config_json;
    tower_config_json.Parse<0>( data_string.c_str() );
    _tower_config = CocosUtils::jsonObjectToValueMap( tower_config_json );
}

void ResourceManager::loadUnitLevelupCostData() {
    FileUtils* file_util = FileUtils::getInstance();
    std::string data_string = file_util->getStringFromFile( "upgrade_cost.json" );
    rapidjson::Document unit_levelup_cost_config_json;
    unit_levelup_cost_config_json.Parse<0>( data_string.c_str() );
    _unit_levelup_cost_config = CocosUtils::jsonObjectToValueMap( unit_levelup_cost_config_json );
}

void ResourceManager::loadBulletData() {
    FileUtils* file_util = FileUtils::getInstance();
    std::string data_string = file_util->getStringFromFile( "bullet.json" );
    rapidjson::Document bullet_config_json;
    bullet_config_json.Parse<0>( data_string.c_str() );
    _bullet_config = CocosUtils::jsonObjectToValueMap( bullet_config_json );
}

void ResourceManager::loadCenterData() {
//    std::string data_string = FileUtils::getInstance()->getStringFromFile( "vision_center.json" );
//    rapidjson::Document vision_config_json;
//    vision_config_json.Parse<0>( data_string.c_str() );
//    _vision_config = CocosUtils::jsonObjectToValueMap( vision_config_json );
}

void ResourceManager::loadBuildingData() {
//    std::string data_string = FileUtils::getInstance()->getStringFromFile( "building.json" );
//    rapidjson::Document building_config_json;
//    building_config_json.Parse<0>( data_string.c_str() );
//    _building_config = CocosUtils::jsonObjectToValueMap( building_config_json );
}

void ResourceManager::loadBattleUIData() {
    FileUtils* file_util = FileUtils::getInstance();
    std::string data_string = file_util->getStringFromFile( "item.json" );
    rapidjson::Document battle_ui_config_json;
    battle_ui_config_json.Parse<0>( data_string.c_str() );
    _battle_ui_config = CocosUtils::jsonObjectToValueMap( battle_ui_config_json );
}

void ResourceManager::loadSkillData() {
    FileUtils* file_util = FileUtils::getInstance();
    std::string data_string = file_util->getStringFromFile( "skill_conf.json" );
    rapidjson::Document skill_config_json;
    skill_config_json.Parse<0>( data_string.c_str() );
    _skill_config = CocosUtils::jsonObjectToValueMap( skill_config_json );
}

void ResourceManager::loadSkillUpgradeCostData() {
    FileUtils* file_util = FileUtils::getInstance();
    std::string data_string = file_util->getStringFromFile( "skill_upgrade_cost.json" );
    rapidjson::Document config_json;
    config_json.Parse<0>( data_string.c_str() );
    _skill_upgrade_cost_config = CocosUtils::jsonObjectToValueMap( config_json );
}

void ResourceManager::loadTeamLevelExpData() {
    FileUtils* file_util = FileUtils::getInstance();
    std::string data_string = file_util->getStringFromFile( "team_level_exp.json" );
    rapidjson::Document level_exp_config_json;
    level_exp_config_json.Parse<0>( data_string.c_str() );
    _team_level_exp_config = CocosUtils::jsonObjectToValueMap( level_exp_config_json );
}

void ResourceManager::loadTeamSkillExpData() {
    FileUtils* file_util = FileUtils::getInstance();
    std::string data_string = file_util->getStringFromFile( "team_skill_exp_conf.json" );
    rapidjson::Document team_skill_exp_config_json;
    team_skill_exp_config_json.Parse<0>( data_string.c_str() );
    _team_skill_exp_config = CocosUtils::jsonObjectToValueMap( team_skill_exp_config_json );
}

void ResourceManager::loadDropData() {
    FileUtils* file_util = FileUtils::getInstance();
    std::string data_string = file_util->getStringFromFile( std::string( DROP_CONFIG_FILE ) + ".json" );
    rapidjson::Document config_json;
    config_json.Parse<0>( data_string.c_str() );
    _drop_config = CocosUtils::jsonObjectToValueMap( config_json );
}

void ResourceManager::loadLevelData() {
    FileUtils* file_util = FileUtils::getInstance();
    std::string data_string = file_util->getStringFromFile( std::string( LEVEL_CONFIG_FILE ) + ".json" );
    rapidjson::Document config_json;
    config_json.Parse<0>( data_string.c_str() );
    _level_config = CocosUtils::jsonObjectToValueMap( config_json );
}

void ResourceManager::loadUnitEffects() {
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile( "effects/fx_unit_common.plist", "effects/fx_unit_common.png" );
    Animation* animation = this->createAnimation( UNIT_BLEED, 5, 0.04, 1 );
    AnimationCache::getInstance()->addAnimation( animation, UNIT_BLEED );
}

void ResourceManager::loadBulletArmature( const std::string& name, const std::string& type ) {
    if( type == "spine" ) {
        std::string path = Utils::stringFormat( "effects/bullets/%s", name.c_str() );
        ArmatureManager::getInstance()->loadArmatureData( path );
    }
    else if( type == "cocos" ) {
        std::string path = Utils::stringFormat( "effects/bullets/%s/skeleton.ExportJson", name.c_str() );
        cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfo( path );
    }
}

void ResourceManager::purgeBulletArmature( const std::string& name, const std::string& type ) {
    if( type == "spine" ) {
        std::string path = Utils::stringFormat( "effects/bullets/%s", name.c_str() );
        ArmatureManager::getInstance()->unloadArmatureData( path );
    }
    else if( type == "cocos" ) {
        std::string path = Utils::stringFormat( "effects/bullets/%s/skeleton.ExportJson", name.c_str() );
        cocostudio::ArmatureDataManager::getInstance()->removeArmatureFileInfo( path );
    }
}

const cocos2d::ValueMap& ResourceManager::getUnitData( const std::string& name ) {
    return _unit_config.at( name ).asValueMap();
}

const cocos2d::ValueMap& ResourceManager::getEquipData( const std::string& equip_id ) {
    return _equip_config.at( equip_id ).asValueMap();
}

const cocos2d::ValueMap& ResourceManager::getTowerData( const std::string& name ) {
    return _tower_config.at( name ).asValueMap();
}

const cocos2d::ValueMap& ResourceManager::getBulletData( const std::string& name ) {
    return _bullet_config.at( name ).asValueMap();
}

const ValueMap& ResourceManager::getSkillData( const std::string& name ) {
    return _skill_config.at( name ).asValueMap();
}

int ResourceManager::getUnitPrice( const std::string& name ) {
    auto itr = _unit_levelup_cost_config.find( name );
    if( itr != _unit_levelup_cost_config.end() ) {
        return itr->second.asValueMap().at( "price" ).asInt();
    }
    return -1;
}

int ResourceManager::getSkillUpgradeCost( const std::string& name, int level ) {
    auto itr = _skill_upgrade_cost_config.find( name );
    if( itr != _skill_upgrade_cost_config.end() ) {
        const ValueVector& costs = itr->second.asValueVector();
        if( level <= costs.size() ) {
            return costs.at( level - 1 ).asInt();
        }
    }
    return -1;
}

int ResourceManager::getUnitUpgradeCost( const std::string& name, int level ) {
    auto itr = _unit_levelup_cost_config.find( name );
    if( itr != _unit_levelup_cost_config.end() ) {
        const ValueVector& costs = itr->second.asValueMap().at( "costs" ).asValueVector();
        if( level <= costs.size() ) {
            return costs.at( level - 1 ).asInt();
        }
    }
    return -1;
}

void ResourceManager::loadUnitArmatures( const cocos2d::ValueVector& armature_names ) {
    for( auto itr = armature_names.begin(); itr != armature_names.end(); ++itr ) {
        std::string unit_name = itr->asString();
        const ValueMap& unit_config = this->getUnitData( unit_name );
        bool is_double_face = unit_config.at( "double_face" ).asBool();
        if( is_double_face ) {
            std::string path = Utils::stringFormat( "characters/%s", unit_name.c_str() );
            ArmatureManager::getInstance()->loadArmatureData( path );
        }
        else {
            std::string front_path = Utils::stringFormat( "characters/%s/%s_f", unit_name.c_str() );
            ArmatureManager::getInstance()->loadArmatureData( front_path );
            std::string back_path = Utils::stringFormat( "chacaters/%s/%s_b", unit_name.c_str() );
            ArmatureManager::getInstance()->loadArmatureData( back_path );
        }
        bool is_melee = unit_config.at( "is_melee" ).asBool();
        if( !is_melee ) {
            auto itr = unit_config.find( "bullet_name" );
            if( itr != unit_config.end() ) {
                std::string bullet_name = itr->second.asString();
                if( bullet_name != "" ) {
                    const cocos2d::ValueMap& single_bullet_config = this->getBulletData( bullet_name );
                    itr = single_bullet_config.find( "body_type" );
                    if( itr != single_bullet_config.end() ) {
                        std::string resource_name = single_bullet_config.at( "name" ).asString() + "_body";
                        std::string type = single_bullet_config.at( "body_type" ).asString();
                        this->loadBulletArmature( resource_name, type );
                    }
                    itr = single_bullet_config.find( "start_type" );
                    if( itr != single_bullet_config.end() ) {
                        std::string resource_name = single_bullet_config.at( "name" ).asString() + "_start";
                        std::string type = itr->second.asString();
                        this->loadBulletArmature( resource_name, type );
                    }
                    itr = single_bullet_config.find( "hit_type" );
                    if( itr != single_bullet_config.end() ) {
                        std::string resource_name = single_bullet_config.at( "hit_name" ).asString() + "_hit";
                        std::string type = single_bullet_config.at( "hit_type" ).asString();
                        this->loadBulletArmature( resource_name, type );
                    }
                }
            }
        }
    }
}

void ResourceManager::purgeUnitArmatures( const cocos2d::ValueVector& armature_names ) {
    for( auto itr = armature_names.begin(); itr != armature_names.end(); ++itr ) {
        std::string unit_name = itr->asString();
        const ValueMap& unit_config = this->getUnitData( unit_name );
        bool is_double_face = unit_config.at( "double_face" ).asBool();
        if( is_double_face ) {
            std::string path = Utils::stringFormat( "characters/%s", unit_name.c_str() );
            ArmatureManager::getInstance()->unloadArmatureData( path );
        }
        else {
            std::string front_path = Utils::stringFormat( "characters/%s/%s_f", unit_name.c_str() );
            ArmatureManager::getInstance()->unloadArmatureData( front_path );
            std::string back_path = Utils::stringFormat( "chacaters/%s/%s_b", unit_name.c_str() );
            ArmatureManager::getInstance()->unloadArmatureData( back_path );
        }
        bool is_melee = unit_config.at( "is_melee" ).asBool();
        if( !is_melee ) {
            auto itr = unit_config.find( "bullet_name" );
            if( itr != unit_config.end() ) {
                std::string bullet_name = itr->second.asString();
                if( bullet_name != "" ) {
                    const ValueMap& single_bullet_config = this->getBulletData( bullet_name );
                    itr = single_bullet_config.find( "body_type" );
                    if( itr != single_bullet_config.end() ) {
                        std::string resource_name = single_bullet_config.at( "name" ).asString() + "_body";
                        std::string type = itr->second.asString();
                        this->purgeBulletArmature( resource_name, type );
                    }
                    itr = single_bullet_config.find( "start_type" );
                    if( itr != single_bullet_config.end() ) {
                        std::string resource_name = single_bullet_config.at( "name" ).asString() + "_start";
                        std::string type = itr->second.asString();
                        this->purgeBulletArmature( resource_name, type );
                    }
                    itr = single_bullet_config.find( "hit_type" );
                    if( itr != single_bullet_config.end() ) {
                        std::string resource_name = single_bullet_config.at( "hit_name" ).asString() + "_hit";
                        std::string type = itr->second.asString();
                        this->purgeBulletArmature( resource_name, type );
                    }
                }
            }
        }
    }
}

void ResourceManager::loadBuildingArmature( const std::string& name ) {
    
}

void ResourceManager::purgeBuildingArmature( const std::string& name ) {
    
}

cocos2d::Animation* ResourceManager::createAnimation( const std::string& name, int count, float delay, int loops ) {
    cocos2d::Vector<cocos2d::SpriteFrame*> frame_array;
    SpriteFrameCache* frame_cache = SpriteFrameCache::getInstance();
    for( int i = 1; i <= count; i++ ) {
        std::string frame_name = Utils::stringFormat( "%s_%02d.png", name.c_str(), i );
        frame_array.pushBack( frame_cache->getSpriteFrameByName( frame_name ) );
    }
    return Animation::createWithSpriteFrames( frame_array, delay, loops );
}

cocos2d::Sprite* ResourceManager::getAnimationSprite( const std::string& name ) {
    return nullptr;
}

std::string ResourceManager::getPathForResource( const std::string& name, eResourceType type ) {
    if( type == eResourceType::Character_Double_Face ) {
        return Utils::stringFormat( "characters/%s", name.c_str() );
    }
    else if( type == eResourceType::Character_Front ) {
        return Utils::stringFormat( "characters/%s/%s_f", name.c_str(), name.c_str() );
    }
    else if( type == eResourceType::Character_Back ) {
        return Utils::stringFormat( "characters/%s/%s_b", name.c_str(), name.c_str() );
    }
    else if( type == eResourceType::Tower ) {
        return Utils::stringFormat( "towers/%s", name.c_str() );
    }
    else {
        return std::string( "" );
    }
}


/*
 dmg damage
 atk atk
 def def
 dod dod
 cri cri
 hit hit
 hp hp
 mp mp
 dur duration
 mov move
 */
std::string ResourceManager::getSkillDesc( const std::string& skill_name, int level ) {
    const ValueMap& skill_conf = this->getSkillConfig().at( skill_name ).asValueMap();
    
    std::string ret = skill_conf.at( "desc" ).asString();
    
    size_t i = ret.find( "dmg" );
    if( i != std::string::npos ) {
        int value = this->getSkillValueOfKey( "damage", skill_conf, level );
        ret.replace( i, 3, Utils::toStr( value ) );
    }
    
    i = ret.find( "atk" );
    if( i != std::string::npos ) {
        int value = this->getSkillValueOfKey( "atk", skill_conf, level );
        ret.replace( i, 3, Utils::toStr( value ) );
    }
    
    i = ret.find( "def" );
    if( i != std::string::npos ) {
        int value = this->getSkillValueOfKey( "def", skill_conf, level );
        ret.replace( i, 3, Utils::toStr( value ) );
    }
    
    i = ret.find( "dod" );
    if( i != std::string::npos ) {
        int value = this->getSkillValueOfKey( "dod", skill_conf, level );
        ret.replace( i, 3, Utils::toStr( value ) );
    }
    
    i = ret.find( "cri" );
    if( i != std::string::npos ) {
        int value = this->getSkillValueOfKey( "cri", skill_conf, level );
        ret.replace( i, 3, Utils::toStr( value ) );
    }
    
    i = ret.find( "hit" );
    if( i != std::string::npos ) {
        int value = this->getSkillValueOfKey( "hit", skill_conf, level );
        ret.replace( i, 3, Utils::toStr( value ) );
    }
    
    i = ret.find( "hp" );
    if( i != std::string::npos ) {
        int value = this->getSkillValueOfKey( "hp", skill_conf, level );
        ret.replace( i, 2, Utils::toStr( value ) );
    }
    
    i = ret.find( "mp" );
    if( i != std::string::npos ) {
        int value = this->getSkillValueOfKey( "mp", skill_conf, level );
        ret.replace( i, 2, Utils::toStr( value ) );
    }
    
    i = ret.find( "dur" );
    if( i != std::string::npos ) {
        int value = this->getSkillValueOfKey( "duration", skill_conf, level );
        ret.replace( i, 3, Utils::toStr( value ) );
    }
    
    i = ret.find( "mov" );
    if( i != std::string::npos ) {
        int value = this->getSkillValueOfKey( "mov", skill_conf, level );
        ret.replace( i, 3, Utils::toStr( value ) );
    }
    
    i = ret.find( "asp" );
    if( i != std::string::npos ) {
        int value = this->getSkillValueOfKey( "asp", skill_conf, level );
        ret.replace( i, 3, Utils::toStr( value ) );
    }
    
    return ret;
}

int ResourceManager::getSkillValueOfKey( const std::string& key, const cocos2d::ValueMap& skill_conf, int level ) {
    auto itr = skill_conf.find( key );
    if( itr != skill_conf.end() ) {
        float v;
        if( itr->second.getType() == Value::Type::VECTOR ) {
            v = itr->second.asValueVector().at( level - 1 ).asFloat();
        }
        else {
            v = itr->second.asFloat();
        }
        if( v < 1.0f ) {
            v *= 100;
        }
        return (int)v;
    }
    return 0;
}