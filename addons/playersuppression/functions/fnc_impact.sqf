/*
 * Author: LAxemann
 * Creates a ppFffect when a bullet impacts nearby
 *
 * Public: Yes
 */
#include "script_component.hpp"

if (((vehicle ACE_player) == ACE_player) || (isTurnedOut ACE_player)) then {
    private ["_rBlur","_cc"];
    // RBlur
    _rBlur = ppEffectCreate ["RadialBlur", 1002]; 
    _rBlur ppEffectAdjust [0.015, 0.015, 0.2, 0.2];
    _rBlur ppEffectCommit 0;
    _rBlur ppEffectEnable true;

    // Color Correction
    _cc = ppEffectCreate ["colorCorrections", 1499];
    _cc ppEffectAdjust [1, 1, 0, [0,0,0,0.4], [1,1,1,1],[1,1,1,0]];
    _cc ppEffectEnable true;
    _cc ppEffectCommit 0;

    _rBlur ppEffectAdjust [0, 0, 0, 0];
    _rBlur ppEffectCommit 0.5;
    _cc ppEffectAdjust [1, 1, 0, [0,0,0,0], [1,1,1,1],[1,1,1,0]];
    _cc ppEffectCommit 0.25;
	
    // Makes the player twitch if it's been a while since he was getting shot at
    if ((time - GVAR(lastShotAt)) >= 120) then {
        addCamShake [3,0.4, 80];
    };
	[FUNC(destroyEffect), 0.5, [time + 0.5, _cc, _rBlur] ] call CBA_fnc_addPerFrameHandler;	
};