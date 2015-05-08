#ifndef __Boids_Net_Def_h_
#define __Boids_Net_Def_h_


//��������˻��и�__msg����
#define HANDLE_MSG(T, PROTO, FUNC) \
	case T: \
		{ \
			PROTO __p; \
			if (__p.ParseFromString(__msg.data())) { \
				FUNC(__p); \
			}\
			else \
			{ \
				cocos2d::log("[ERROR] Parse %s failed", #PROTO); \
			} \
		} \
		break;

//�������и�__msg������sessionptr����
#define HANDLE_MSG_SESSION(T, PROTO, FUNC) \
	case T: \
		{ \
			PROTO __p; \
			if (__p.ParseFromString(__msg.data())) { \
				FUNC(sessionptr, __p); \
			}\
			else \
			{ \
				cocos2d::log("[ERROR] Parse %s failed", #PROTO); \
			} \
		} \
		break;

#endif