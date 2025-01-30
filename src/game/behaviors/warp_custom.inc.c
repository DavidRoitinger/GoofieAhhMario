void bhv_warp_custom_loop(void) {
    o->oPosY = 100.0f;
    o->hitboxRadius = 10.0f;

    if(((o->oBehParams >> 24) == 1 && gMarioState->MainArea)||
        ((o->oBehParams >> 24) == 0 && gMarioState->CombatArea)){
        o->oPosY = 0.0f;
        o->hitboxRadius = 1000.0f;
    }else{
        o->oPosY = 10000.0f;
        o->hitboxRadius = 0.0f;
    }

    o->oInteractStatus = INT_STATUS_NONE;
}