#pragma once

#include "extdll.h"
#include "util.h"
#include "cbase.h"

class CEnvModel : public CBaseAnimating {
private:
    void Spawn();
};

LINK_ENTITY_TO_CLASS(env_model, CEnvModel);

void CEnvModel::Spawn(){
    PRECACHE_MODEL((char*)STRING(pev->model));
    SET_MODEL(edict(), STRING(pev->model));
}