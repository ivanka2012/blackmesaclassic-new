#pragma once

#include "extdll.h"
#include "util.h"
#include "cbase.h"
#include <string_view>
#include <string>
#include <charconv>
#include <optional>

std::optional<int> ConvertFromString(std::string_view inputStr){
    int outputInt;
    auto [ptr, ec] = std::from_chars(inputStr.data(), inputStr.data()+inputStr.size(), outputInt);
    if(ec == std::errc{}){
        return {};
    }else{
        return outputInt;
    }
}

bool HandleStringConv(std::string_view keyStr, std::string_view valueStr, int& val){
    auto parsedInt = ConvertFromString(valueStr);
    if(parsedInt.has_value()){
        val = parsedInt.value();
        return true;
    }else{
        ALERT(at_error, "\"%s\" is invalid for the \"%s\" key of env_model", valueStr, keyStr);
        return false;
    }
}

class CEnvModel : public CBaseAnimating {
    std::string modelName;
    int body, skin, sequence, framerate, scale;
public:
    void Spawn();
    void Precache();
    void KeyValue(KeyValueData *pkvd);
};

LINK_ENTITY_TO_CLASS(env_model, CEnvModel);

void CEnvModel::Spawn(){
    Precache();

    SET_MODEL(edict(), modelName.c_str());

    pev->sequence = sequence;
    pev->framerate = float(framerate);
    pev->scale = float(scale);
    pev->body = body;
    pev->skin = skin;
}

void CEnvModel::Precache(){
    //The cunt needs the pointer to be mutable. I don't want to find out why
    PRECACHE_MODEL(modelName.data());

    CBaseAnimating::Precache();
}

void CEnvModel::KeyValue(KeyValueData *pkvd){
    std::string_view keyStr{pkvd->szKeyName};
    std::string_view valueStr{pkvd->szValue};
    if(keyStr == "model"){
        modelName = valueStr;
        pkvd->fHandled = TRUE;
    }else if(keyStr == "body"){
        HandleStringConv(keyStr, valueStr, body);
        pkvd->fHandled = TRUE;
    }else if(keyStr == "skin"){
        HandleStringConv(keyStr, valueStr, skin);
        pkvd->fHandled = TRUE;
    }else if(keyStr == "sequence"){
        HandleStringConv(keyStr, valueStr, sequence);
        pkvd->fHandled = TRUE;
    }else if(keyStr == "framerate"){
        HandleStringConv(keyStr, valueStr, framerate);
        pkvd->fHandled = TRUE;
    }else if(keyStr == "scale"){
        HandleStringConv(keyStr, valueStr, scale);
        pkvd->fHandled = TRUE;
    }else{
        CBaseAnimating::KeyValue(pkvd);
    }
}