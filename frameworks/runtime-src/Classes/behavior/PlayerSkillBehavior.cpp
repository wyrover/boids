//
//  PlayerSkillBehavior.cpp
//  Boids
//
//  Created by Yanjie Chen on 3/11/15.
//
//

#include "PlayerSkillBehavior.h"
#include "../scene/BattleLayer.h"

using namespace cocos2d;

#define DEFAULT_CATCH_UP_DISTANCE 80.0

PlayerSkillBehavior::PlayerSkillBehavior() {

}

PlayerSkillBehavior::~PlayerSkillBehavior() {
    
}

PlayerSkillBehavior* PlayerSkillBehavior::create( class TargetNode* unit_node ) {
    PlayerSkillBehavior* ret = new PlayerSkillBehavior();
    if( ret && ret->init( unit_node ) ) {
        ret->autorelease();
        return ret;
    }
    else {
        CC_SAFE_DELETE( ret );
        return nullptr;
    }
}

bool PlayerSkillBehavior::init( TargetNode* unit_node ) {
    if( !BehaviorBase::init( unit_node ) ) {
        return false;
    }
    _elapse = 0;
    return true;
}

bool PlayerSkillBehavior::behave( float delta ) {
    UnitNode* unit_node = dynamic_cast<UnitNode*>( _target_node );
    if( unit_node->isDying() ) {
        return true;
    }
    if( unit_node->isUnderControl() ) {
        return true;
    }
    if( unit_node->isCasting() || unit_node->willCast() ) {
        return true;
    }
    if( unit_node->isCharging() ) {
        return false;
    }
    BattleLayer* battle_layer = unit_node->getBattleLayer();
    Point control_dir = battle_layer->getControlLayer()->getJoyStickDirection();
    if( control_dir.x != 0 || control_dir.y != 0 ) {
        return false;
    }
    
    if( unit_node->getChasingTarget() != nullptr ) {
        cocos2d::Point target_pos = unit_node->getChasingTarget()->getPosition();
        cocos2d::Point unit_pos = unit_node->getPosition();
        float distance = target_pos.distance( unit_pos );
        _elapse += delta;
        if( _elapse >= 1.0f ) {
            _elapse = 0;
            int skill_count = (int)unit_node->getSkills().size();
            for( int i = 1; i < skill_count; i++ ) {
                float range = unit_node->getSkillRangeById( i );
                if( ( range == 0 || distance <= range ) && unit_node->isSkillReadyById( i ) && Utils::randomFloat() < 0.5 ) {
                    unit_node->useSkill( i, unit_node->getUnitDirection(), 0, 0 );
                    return true;
                }
            }
        }
    }
    return false;
}