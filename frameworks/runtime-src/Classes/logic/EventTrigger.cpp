//
//  EventTrigger.cpp
//  Boids
//
//  Created by Yanjie Chen on 3/8/15.
//
//

#include "EventTrigger.h"
#include "../util/CocosUtils.h"
#include "MapLogic.h"
#include "../unit/UnitNode.h"
#include "../constant/BoidsConstant.h"
#include "../scene/BattleLayer.h"

using namespace cocos2d;

EventTrigger::EventTrigger() {
    
}

EventTrigger::~EventTrigger() {
    
}

EventTrigger* EventTrigger::create( const ValueMap& event_data ) {
    EventTrigger* ret = new EventTrigger();
    if( ret && ret->init( event_data ) ) {
        ret->autorelease();
        return ret;
    }
    else {
        CC_SAFE_DELETE( ret );
        return nullptr;
    }
}

bool EventTrigger::init( const ValueMap& event_data ) {
    _current_trigger_index = 0;
    _is_enabled = true;
    
    _event_data = event_data;
    const ValueMap& meta_data = event_data.at( "trigger_meta" ).asValueMap();
    auto itr = meta_data.find( "trigger_relation" );
    if( itr == meta_data.end() ) {
        _relation = "then";
    }
    else {
        _relation = itr->second.asString();
    }
    itr = meta_data.find( "is_repeated" );
    if( itr == meta_data.end() ) {
        _is_repeat = false;
    }
    else {
        _is_repeat = itr->second.asBool();
    }
    
    const ValueVector& trigger_data = event_data.at( "triggers" ).asValueVector();
    _total_trigger_count = (int)trigger_data.size();
    for( auto itr = trigger_data.begin(); itr != trigger_data.end(); ++itr ) {
        Trigger* trigger = Trigger::create( itr->asValueMap() );
        this->addTrigger( trigger );
    }
    
    return true;
}

void EventTrigger::setEnabled( bool b ) {
    _is_enabled = b;
}

bool EventTrigger::canFire() {
    if( _relation == "then" ) {
        return _triggers.at( _current_trigger_index )->couldTrigger();
    }
    else if( _relation == "or" ) {
        for( auto itr = _triggers.begin(); itr != _triggers.end(); ++itr ) {
            if( (*itr)->couldTrigger() ) {
                return true;
            }
        }
        return false;
    }
    else if( _relation == "and" ) {
        for( auto itr = _triggers.begin(); itr != _triggers.end(); ++itr ) {
            if( !(*itr)->couldTrigger() ) {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool EventTrigger::isEnabled() {
    return _is_enabled;
}

void EventTrigger::moveOn() {
    bool should_check = false;
    if( ++_current_trigger_index >= _total_trigger_count && _relation == "then" ) {
        should_check = true;
    }
    else if( _relation == "or" ) {
        should_check = true;
    }
    else if( _relation == "and" ) {
        should_check = true;
    }
    if( should_check ) {
        if( _is_repeat ) {
            _current_trigger_index = 0;
            for( auto trigger : _triggers ) {
                trigger->setCouldTrigger( false );
            }
        }
        else {
            this->setEnabled( false );
        }
    }
}

void EventTrigger::trigger( class MapLogic* map_logic, class UnitNode* unit_node ) {
    const cocos2d::ValueVector& actions = _event_data.at( "actions" ).asValueVector();
    int action_count = (int)actions.size();
    for( int i = 0; i < action_count; ++i ) {
        const ValueMap& action = actions.at( i ).asValueMap();
        EventAction* ea = EventAction::create( action, map_logic, this );
        map_logic->addEventAction( ea, ea->getActionName() );
        cocos2d::Map<std::string, cocos2d::Ref*> params;
        if( unit_node ) {
            params.insert( "unit", unit_node );
        }
        else {
            params.insert( "unit", Node::create() );
        }
        Node* node = Node::create();
        node->setTag( i );
        params.insert( "idx", node );
        ea->start( params, true );
    }
    this->moveOn();
}

void EventTrigger::checkTriggerPass( class MapLogic* map_logic, class UnitNode* unit_node ) {
    if( this->canFire() ) {
        this->trigger( map_logic, unit_node );
    }
}

void EventTrigger::activateTriggerByConditions( const cocos2d::ValueMap& conditions, class MapLogic* map_logic, class UnitNode* unit_node ) {
    if( _relation == "then" ) {
        _triggers.at( _current_trigger_index )->updateTrigger( conditions );
    }
    else {
        for( auto trigger : _triggers ) {
            trigger->updateTrigger( conditions );
        }
    }
    this->checkTriggerPass( map_logic, unit_node );
}

void EventTrigger::activateTriggerByUnit( class MapLogic* map_logic, class UnitNode* unit, const std::string& unit_state, const cocos2d::ValueMap& area ) {
    if( _relation == "then" ) {
        _triggers.at( _current_trigger_index )->updateTrigger( map_logic, unit, unit_state );
    }
    else {
        for( auto trigger : _triggers ) {
            trigger->updateTrigger( map_logic, unit, unit_state );
        }
    }
    this->checkTriggerPass( map_logic, unit );
}

void EventTrigger::addTrigger( Trigger* trigger ) {
    _triggers.pushBack( trigger );
}