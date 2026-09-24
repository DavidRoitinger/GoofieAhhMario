void bhv_warp_custom_loop(void) {
    o->oPosY = 100.0f;
    o->hitboxRadius = 10.0f;

    if(gMarioState->transDelay >= 0){
    // if(((o->oBehParams >> 24) == COMBAT && gMarioState->gameType == OVERWORLD)||
    //     ((o->oBehParams >> 24) == OVERWORLD && gMarioState->gameType == COMBAT)){
        o->oPosY = 0.0f;
        o->hitboxRadius = 1000.0f;
    }else{
        o->oPosY = 10000.0f;
        o->hitboxRadius = 0.0f;
    }

    o->oInteractStatus = INT_STATUS_NONE;
}