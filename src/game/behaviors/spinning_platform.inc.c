void bhv_spinning_block(void) {

    //print_text(100, 100, o->oBehParams2ndByte << 5);
    //gMarioState->numStars = o->oBehParams2ndByte;

    o->oAngleVelYaw = o->oBehParams2ndByte << 5;

    o->oFaceAngleYaw += o->oAngleVelYaw;
}