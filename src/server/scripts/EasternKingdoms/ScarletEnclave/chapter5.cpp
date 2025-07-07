/*
 * Copyright (C) 2008-2019 TrinityCore <https://www.trinitycore.org/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/*Script made from scratch by Hellfrost
Designed to be as blizzlike as possible through functionality, but to improve
upon blizzard's rendition to make it feel more cinematic, responsive and functional*/

#include "ScriptMgr.h"
#include "GameObject.h"
#include "Map.h"
#include "MotionMaster.h"
#include "ObjectAccessor.h"
#include "Player.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "TemporarySummon.h"
#include "WaypointDefines.h"
#include "GridDefines.h"

//npc related info
enum npc_info
{
    //scourge npc IDS
    ID_FLESH_BEHEMOTH = 29190,
    ID_RAMPAGING_ABOMINATION = 29186,
    ID_WARRIOR_OF_THE_FROZEN_WASTES = 29206,
    ID_VOLATILE_GHOUL = 29219,
    ID_HIGHLORD_DARION_MOGRAINE = 29173,
    ID_KOLTIRA_DEATHWEAVER = 29199,
    ID_ORBAZ_BLOODBANE = 29204,
    ID_THASSARIAN = 29200,

    //light's hope npc IDS
    ID_DEFENDER_OF_THE_LIGHT = 29174,
    ID_LORD_MAXWELL_TYROSUS = 29178,
    ID_KORFAX_CHAMPION_OF_THE_LIGHT = 29176,
    ID_LEONID_BARTHALOMEW_THE_REVERED = 29179,
    ID_DUKE_NICHOLAS_ZVERENHOFF = 29180,
    ID_COMMANDER_ELIGOR_DAWNBRINGER = 29177,
    ID_RAYNE = 29181,
    ID_RIMBLAT_EARTHSHATTER = 29182,
    ID_HIGHLORD_TIRION_FORDRING = 29175,

    //other
    ID_THE_LICH_KING = 29183,
    ID_HIGHLORD_ALEXANDROS_MOGRAINE = 29227,
    ID_YOUNG_DARION_MOGRAINE = 29228,
};

//npc creature_text ids
enum npc_text_info
{
    DARION_EVENT_WAITING_FOR_BATTLE_1 = 0, // pre text
    DARION_EVENT_WAITING_FOR_BATTLE_2 = 1,
    DARION_EVENT_WAITING_FOR_BATTLE_3 = 2,
    DARION_EVENT_OPENING_SCENE_1 = 3, // soldiers of the scourge
    DARION_EVENT_OPENING_SCENE_2 = 4, // RISE
    DARION_EVENT_OPENING_SCENE_3 = 5, // the skies turn red
    KORFAX_CHARGING_INTO_BATTLE = 6, // During the fight - Korfax, Champion of the Light
    MAXWELL_IN_BATTLE = 7, // Lord Maxwell Tyrosus
    DARION_IN_BATTLE = 8, // Highlord Darion Mograine
    TIRION_EVENT_SPAWNED = 24, // After the fight
    TIRION_BATTLE_LOST_1 = 25, // Highlord Tirion Fordring
    DARION_BATTLE_LOST_1 = 26, // Highlord Darion Mograine
    TIRION_BATTLE_LOST_2 = 27, // Highlord Tirion Fordring
    TIRION_BATTLE_LOST_3 = 28, // Highlord Tirion Fordring
    TIRION_BATTLE_LOST_4 = 29, // Highlord Tirion Fordring
    DARION_BATTLE_LOST_2 = 30, // Highlord Tirion Fordring
    ALEXANDROS_FLASH_BACK_1 = 31, // Highlord Alexandros Mograine
    DARION_FLASH_BACK_1 = 32, // Highlord Darion Mograine
    DARION_FLASH_BACK_2 = 33, // Highlord Darion Mograine
    YOUNG_DARION_FLASH_BACK_1 = 34, // Darion Mograine
    YOUNG_DARION_FLASH_BACK_3 = 35, // Darion Mograine
    ALEXANDROS_FLASH_BACK_2 = 36, // Highlord Alexandros Mograine
    YOUNG_DARION_FLASH_BACK_4 = 37, // Darion Mograine
    ALEXANDROS_FLASH_BACK_3 = 38, // Highlord Alexandros Mograine
    YOUNG_DARION_FLASH_BACK_5 = 39, // Darion Mograine
    ALEXANDROS_FLASH_BACK_4 = 40, // Highlord Alexandros Mograine
    ALEXANDROS_FLASH_BACK_5 = 41, // Highlord Alexandros Mograine
    LICH_KING_FLASH_BACK_1 = 42, // The Lich King
    DARION_FLASH_BACK_3 = 43, // Highlord Darion Mograine
    LICH_KING_FLASH_BACK_2 = 44, // The Lich King
    LICH_KING_FLASH_BACK_3 = 45, // The Lich King
    TIRION_FLASH_BACK_1 = 46, // Highlord Tirion Fordring
    LICH_KING_FLASH_BACK_4 = 47, // The Lich King
    LICH_KING_FLASH_BACK_5 = 48, // The Lich King
    MAXWELL_FLASH_BACK_1 = 49, // Lord Maxwell Tyrosus
    LICH_KING_FLASH_BACK_6 = 50, // The Lich King
    DARION_FLASH_BACK_4 = 51, // Highlord Darion Mograine
    DARION_FLASH_BACK_5 = 52, // Highlord Darion Mograine
    TIRION_FLASH_BACK_2 = 53, // Highlord Tirion Fordring
    LICH_KING_FLASH_BACK_7 = 54, // The Lich King
    TIRION_FLASH_BACK_3 = 55, // Highlord Tirion Fordring
    LICH_KING_FLASH_BACK_8 = 56, // The Lich King
    LICH_KING_FLASH_BACK_9 = 57, // The Lich King
    LICH_KING_FLASH_BACK_10 = 58, // The Lich King
    TIRION_FLASH_BACK_4 = 59, // Highlord Tirion Fordring
    TIRION_FLASH_BACK_5 = 60, // Highlord Tirion Fordring
    TIRION_FLASH_BACK_6 = 61, // Highlord Tirion Fordring
    TIRION_FLASH_BACK_7 = 62, // Highlord Tirion Fordring
    TIRION_FLASH_BACK_8 = 63, // Highlord Tirion Fordring
    TIRION_FLASH_BACK_9 = 64, // Highlord Tirion Fordring
    TIRION_FLASH_BACK_10 = 65, // Highlord Tirion Fordring
    TIRION_FLASH_BACK_11 = 66, // Highlord Tirion Fordring
    DARION_FLASH_BACK_6 = 67, // Highlord Darion Mograine

    ORBAZ_FLEES_FROM_BATTLE = 71,
    YOUNG_DARION_FLASH_BACK_2 = 75,
    TIRION_FLASH_BACK_12 = 79,
    DARION_COLLAPSE = 82,
    SPECIAL_DAWN_NPC_DEFEATED = 86,
    DARION_KNEEL_BEFORE_TIRION = 87
};

//spell ids
enum npc_spell_info
{
    SPELL_SCOURGE_MINION_BIRTH_EFFECT = 35177,
    SPELL_PLAYER_CAMERA_SHAKE = 69235,
    SPELL_QUEST_COMPLETE = 53606,

    //flesh behemoth
    SPELL_STOMP = 53634,
    SPELL_THUNDERCLAP = 36706,
    //rampaging abomination
    SPELL_CLEAVE = 53633,
    SPELL_SCOURGE_HOOK = 50335,
    //warrior of the frozen wastes
    //SPELL_CLEAVE = 53633, uses the same one as rampaging abomination
    //volatile ghoul
    SPELL_GHOULSPLOSION = 53632,
    //koltira, orbaz and thassarian
    SPELL_PLAGUE_STRIKE = 50688,
    //defender of the light
    SPELL_HOLY_LIGHT_DEFENDER = 29427,
    SPELL_HOLY_STRIKE = 53643,
    SPELL_UPPERCUT = 53629,
    //korfax, champion of the light
    //SPELL_CLEAVE = 53633, uses the same one as rampaging abomination
    //commander eligor dawnbringer
    SPELL_HOLY_LIGHT_ELIGOR = 37979,
    //rayne
    SPELL_REJUVENATION = 20664,
    SPELL_STARFALL = 20687,
    SPELL_WRATH = 21807,
    //rimblat earthshatter
    SPELL_CHAIN_HEAL = 33642,
    SPELL_THUNDER = 53630,
    //highlord darion mograine
    SPELL_THE_MIGHT_OF_MOGRAINE = 53642,
    SPELL_DEATHS_EMBRACE = 53635,
    SPELL_ICY_TOUCH = 49723,
    SPELL_UNHOLY_BLIGHT = 53641,
    SPELL_ANTI_MAGIC_ZONE = 51052,
    SPELL_DARION_CHARGE_AT_LICH_KING = 53679,
    SPELL_THROW_ASHBRINGER = 53701,
    //special dawn npcs when defeated
    SPELL_FEIGN_DEATH = 57626,
    //highlord tirion fordring
    SPELL_LIGHT_OF_DAWN_KILL = 53644,
    SPELL_LIGHT_OF_DAWN_PRISON = 53658,
    SPELL_REBIRTH_OF_THE_ASHBRINGER = 53702,
    SPELL_TIRION_CHARGE = 53706,
    SPELL_LAY_ON_HANDS = 53778,
    //kneel spell
    SPELL_KNEEL = 68442,
    //alexandros spawn spell
    SPELL_ALEXANDROS_SPAWN = 53667,
    //lich king spells
    SPELL_DRAIN_ALEXANDROS = 53677,
    SPELL_DRAIN_TIRION = 53685,
    SPELL_APOCALYPSE = 53210,
    SPELL_APOCALYPSE_SECONDARY = 53745,
    SPELL_REBUKE = 53680,
    SPELL_EXIT_TELEPORT_VISUAL = 61456
};

enum event_misc
{
    //max number of spawned creatures
    NUMBER_FLESH_BEHEMOTH = 2,
    NUMBER_RAMPAGING_ABOMINATION = 3,
    NUMBER_WARRIOR_OF_THE_FROZEN_WASTES = 8,
    NUMBER_VOLATILE_GHOUL = 40,
    NUMBER_DEFENDER_OF_THE_LIGHT = 20,

    //number of dawn left to trigger losing battle phase
    NUMBER_DAWN_FORCES_FOR_BATTLE_END = 200,

    //number of summoned holy lightning gameobjects (each)
    NUMBER_HOLY_LIGHTNING = 15,

    //creature target aquisition range
    COMBAT_TARGET_AQUISITION_RANGE = 150,

    //creature invincibility hp
    INVINCIBILITY_HP = 1,

    //event worldstate default values
    ENCOUNTER_TOTAL_DAWN = 300,
    ENCOUNTER_TOTAL_SCOURGE = 10000,
    ECOUNTER_COUNTDOWN_TIME_MINUTES = 5,
    EVENT_TIMER_RESET_COOLDOWN = 5,

    //event worldstate ids
    WORLD_STATE_DEFENDERS_COUNT = 3590,
    WORLD_STATE_SCOURGE_COUNT = 3591,
    WORLD_STATE_SOLDIERS_ENABLE = 3592,
    WORLD_STATE_COUNTDOWN_ENABLE = 3603,
    WORLD_STATE_COUNTDOWN_TIME = 3604,
    WORLD_STATE_EVENT_BEGIN_ENABLE = 3605,

    //game objects spawned
    OBJECT_HOLY_LIGHTNING_HORIZONTAL = 191301,
    OBJECT_HOLY_LIGHTNING_VERTICAL = 191302,
    OBJECT_LIGHT_OF_DAWN = 191330
};

//all creature spawn locations
//scourge units before battle
Position const Spawn_Positions_Flesh_Behemoth[] =
{
    {2453.18f, -5183.31f, 76.1869f, 3.22886f},
    {2435.99f, -5097.61f, 82.9616f, 5.06145f}
};
Position const Spawn_Positions_Warrior_Of_The_Frozen_Wastes[] =
{
    {2428.6f, -5168.69f, 80.3161f, 1.49656f},
    {2412.01f, -5157.7f, 82.2834f, 0.828971f},
    {2443.45f, -5166.73f, 79.4432f, 1.95995f},
    {2434.55f, -5151.58f, 82.9315f, 1.81466f},
    {2429.71f, -5123.31f, 81.4721f, 4.85808f},
    {2445.7f, -5138.54f, 80.5069f, 3.06345f},
    {2423.38f, -5138.32f, 83.7021f, 0.102478f},
    {2410.08f, -5170.45f, 80.8811f, 1.01747f}
};
Position const Spawn_Positions_Volatile_Ghoul[] =
{
    {2416.17f, -5123.57f, 81.5519f, 5.55315f},
    {2448.14f, -5144.21f, 79.9286f, 2.76108f},
    {2449.37f, -5134.79f, 79.482f, 3.29908f},
    {2446.1f, -5117.12f, 77.7133f, 4.11982f},
    {2439.7f, -5119.44f, 79.1208f, 4.28867f},
    {2426.25f, -5103.97f, 81.6615f, 4.94449f},
    {2435.89f, -5110.04f, 79.5881f, 4.54393f},
    {2405.31f, -5177.1f, 79.4725f, 0.997847f},
    {2417.64f, -5172.57f, 79.8871f, 1.1942f},
    {2452.85f, -5126.25f, 77.7558f, 3.64072f},
    {2437.77f, -5144.56f, 82.4358f, 2.30555f},
    {2414.25f, -5130.58f, 82.8024f, 5.89873f},
    {2420.95f, -5118.86f, 80.5602f, 5.239f},
    {2419.34f, -5110.17f, 80.2288f, 5.15261f},
    {2442.56f, -5108.4f, 78.4391f, 4.35151f},
    {2399.34f, -5168.23f, 78.6042f, 0.805433f},
    {2446.36f, -5127.03f, 79.1348f, 3.77424f},
    {2432.06f, -5158.97f, 82.8595f, 1.61047f},
    {2443.49f, -5153.16f, 80.2963f, 2.29377f},
    {2408.12f, -5164.83f, 80.8734f, 0.852548f},
    {2404.32f, -5156.75f, 81.5205f, 0.620855f},
    {2407.63f, -5144.11f, 84.2107f, 0.298839f},
    {2419.94f, -5143.8f, 84.4435f, 0.499116f},
    {2439.92f, -5125.08f, 80.2903f, 4.08054f},
    {2428.24f, -5114.38f, 79.7844f, 4.87771f},
    {2433.7f, -5123.51f, 81.1135f, 4.56749f},
    {2426.79f, -5143.75f, 84.3152f, 0.942866f},
    {2412.67f, -5137.8f, 83.7095f, 0.0200226f},
    {2423.49f, -5129.56f, 82.9326f, 5.54923f},
    {2412.51f, -5150.65f, 84.2838f, 0.605144f},
    {2446.02f, -5192.31f, 77.0883f, 1.82644f},
    {2401.32f, -5148.85f, 82.7064f, 0.377382f},
    {2395.84f, -5155.9f, 79.2325f, 0.487338f},
    {2426.73f, -5178.36f, 78.0861f, 1.46123f},
    {2436.97f, -5175.2f, 78.1798f, 1.74005f},
    {2450.04f, -5169.95f, 79.1399f, 2.08562f},
    {2435.71f, -5165.82f, 80.3542f, 1.71649f},
    {2432.37f, -5189.56f, 77.4219f, 1.58297f},
    {2439.67f, -5196.04f, 77.256f, 1.71256f},
    {2418.66f, -5182.96f, 76.8548f, 1.31594f}
};
Position const Spawn_Positions_Koltira_Deathweaver = Position(2438.45f, -5137.02f, 82.6968f, 4.13643f);
Position const Spawn_Positions_Orbaz_Bloodbane = Position(2436.04f, -5132.31f, 82.8884f, 3.90954f);
Position const Spawn_Positions_Thassarian = Position(2431.82f, -5130.47f, 83.3011f, 4.04916f);

//scourge units during battle
Position const Spawn_Positions_Flesh_Behemoth_Battle[] =
{
    {2221.49f, -5251.8f, 76.5902f, 5.747f},
    {2355.98f, -5253.87f, 82.4865f, 3.48898f}
};
Position const Spawn_Positions_Rampaging_Abomination_Battle[] =
{
    {2280.07f, -5231.14f, 82.1066f, 4.71813f},
    {2214.19f, -5290.29f, 84.0677f, 0.0410819f},
    {2352.37f, -5274.75f, 81.0429f, 3.28478f}
};
Position const Spawn_Positions_Warrior_Of_The_Frozen_Wastes_Battle[] =
{
    {2337.04f, -5277.43f, 81.7331f, 3.20615f},
    {2227.07f, -5289.6f, 80.9875f, 0.115605f},
    {2327.18f, -5260.03f, 83.4187f, 3.69307f},
    {2310.56f, -5248.68f, 84.3513f, 4.01509f},
    {2291.13f, -5245.63f, 83.0093f, 4.45491f},
    {2273.05f, -5247.86f, 77.6256f, 4.95756f},
    {2254.7f, -5255.19f, 76.2138f, 5.3856f},
    {2235.68f, -5268.42f, 76.2547f, 5.88433f}
};
Position const Spawn_Positions_Volatile_Ghoul_Battle[] =
{
    {2219.85f, -5293.82f, 82.2782f, 0.0803461f},
    {2219.37f, -5286.27f, 82.231f, 6.27714f},
    {2219.78f, -5278.73f, 80.8165f, 6.12006f},
    {2222.52f, -5270.11f, 77.7931f, 5.97476f},
    {2229.24f, -5262.4f, 75.1403f, 5.77841f},
    {2238.64f, -5255.41f, 74.4939f, 5.64097f},
    {2246.37f, -5247.25f, 75.9995f, 5.42892f},
    {2256.78f, -5244.0f, 78.0077f, 5.2954f},
    {2266.9f, -5239.0f, 79.8665f, 4.99695f},
    {2276.26f, -5238.37f, 80.3334f, 4.79274f},
    {2284.66f, -5237.24f, 82.2231f, 4.6553f},
    {2293.01f, -5236.34f, 83.8477f, 4.50215f},
    {2301.76f, -5236.9f, 84.4308f, 4.31366f},
    {2310.16f, -5239.13f, 84.4777f, 4.1448f},
    {2317.15f, -5243.63f, 84.6377f, 3.9563f},
    {2324.63f, -5249.1f, 84.4826f, 3.88169f},
    {2331.94f, -5255.38f, 84.028f, 3.73638f},
    {2337.58f, -5262.83f, 82.3912f, 3.47327f},
    {2342.84f, -5272.12f, 81.4946f, 3.3476f},
    {2345.86f, -5281.75f, 82.1256f, 3.1591f},
    {2344.42f, -5276.87f, 81.5793f, 3.24156f},
    {2340.37f, -5266.9f, 81.7609f, 3.45755f},
    {2335.04f, -5259.06f, 83.2399f, 3.5086f},
    {2328.06f, -5252.33f, 84.3141f, 3.74422f},
    {2321.19f, -5246.76f, 84.582f, 3.90523f},
    {2313.62f, -5241.66f, 84.5411f, 4.01911f},
    {2306.44f, -5236.96f, 84.6126f, 4.20368f},
    {2297.65f, -5236.41f, 84.2234f, 4.38432f},
    {2289.1f, -5236.63f, 83.266f, 4.47856f},
    {2280.45f, -5237.88f, 81.2111f, 4.73381f},
    {2271.28f, -5238.71f, 79.8063f, 4.93015f},
    {2262.12f, -5241.72f, 79.0038f, 5.11864f},
    {2251.78f, -5246.06f, 76.8774f, 5.27571f},
    {2242.05f, -5250.7f, 75.0714f, 5.55059f},
    {2233.83f, -5259.19f, 74.4987f, 5.5231f},
    {2225.69f, -5265.99f, 76.3248f, 5.91187f},
    {2220.91f, -5274.68f, 79.3227f, 6.11607f},
    {2219.44f, -5282.81f, 81.8199f, 6.1946f},
    {2219.58f, -5290.08f, 82.3034f, 0.00958824f},
    {2227.35f, -5301.7f, 81.4263f, 0.363003f}
};

//dawn units
Position const Spawn_Positions_Defender_of_the_Light = Position(2298.75f, -5341.6f, 90.8799f, 2.16171f);
Position const defender_of_the_light_ready_location[] =
{
    {2287.44f, -5281.44f, 82.2658f, 0.703251f},
    {2314.83f, -5300.09f, 81.9951f, 1.24125f},
    {2303.31f, -5288.1f, 81.9951f, 0.934943f},
    {2295.51f, -5284.28f, 81.9233f, 0.783361f},
    {2309.69f, -5294.39f, 81.9963f, 1.1093f},
    {2275.45f, -5281.41f, 82.2612f, 0.575232f},
    {2250.45f, -5303.48f, 82.1681f, 0.579154f},
    {2257.81f, -5289.28f, 82.0154f, 0.49276f},
    {2266.34f, -5284.92f, 81.9315f, 0.473125f},
    {2252.65f, -5296.15f, 82.1673f, 0.606646f},
    {2260.24f, -5304.83f, 82.1329f, 0.712668f},
    {2261.48f, -5299.23f, 82.1672f, 0.606639f},
    {2264.64f, -5295.46f, 82.1672f, 0.653763f},
    {2270.01f, -5292.55f, 82.6137f, 0.606639f},
    {2276.67f, -5289.45f, 83.0341f, 0.587004f},
    {2285.19f, -5290.25f, 83.3859f, 0.78728f},
    {2292.16f, -5291.39f, 81.9969f, 0.736229f},
    {2298.74f, -5295.19f, 81.9969f, 0.940433f},
    {2305.54f, -5300.5f, 81.9969f, 1.08573f},
    {2309.5f, -5305.0f, 81.9968f, 1.14071f}
};
Position const Spawn_Positions_Lord_Maxwell_Tyrosus = Position(2280.95f, -5294.73f, 84.0877f, 0.783359f);
Position const Spawn_Positions_Korfax_Champion_of_the_Light = Position(2281.12f, -5302.55f, 85.6199f, 0.830486f);
Position const Spawn_Positions_Leonid_Barthalomew_the_Revered = Position(2276.25f, -5302.39f, 85.2913f, 0.806922f);
Position const Spawn_Positions_Duke_Nicholas_Zverenhoff = Position(2286.14f, -5302.75f, 85.8195f, 0.905098f);
Position const Spawn_Positions_Commander_Eligor_Dawnbringer = Position(2281.01f, -5308.37f, 86.8253f, 0.806919f);
Position const Spawn_Positions_Rayne = Position(2296.54f, -5303.6f, 81.9968f, 0.967914f);
Position const Spawn_Positions_Rimblat_Earthshatter = Position(2303.04f, -5307.04f, 81.9968f, 1.16426f);
Position const Spawn_Positions_Highlord_Tirion_Fordring = Position(2193.17f, -5280.34f, 92.5124f, 6.09926f);

//other
Position const Spawn_Positions_Highlord_Alexandros_Mograine = Position(2281.1f, -5262.17f, 81.011f, 4.70177f);
Position const Spawn_Positions_Young_Darion = Position(2280.75f, -5279.95f, 82.3167f, 1.55232f);
Position const Spawn_Positions_Lich_King = Position(2281.46f, -5256.08f, 80.0608f, 4.68214f);

//all pathing data
Position const darion_to_lights_hope = Position(2280.18f, -5286.24f, 82.8566f, 4.83053f);
Position const scourgeMinion_to_lights_hope_1 = Position(2306.38f, -5292.06f, 81.9964f, 3.72314f);
Position const scourgeMinion_to_lights_hope_2 = Position(2251.42f, -5301.95f, 82.1678f, 5.7848f);
Position const scourgeMinion_respawn_battle = Position(2280.87f, -5285.37f, 82.7648f, 4.77451f);
Position const highlord_tirion_fordring_to_lights_hope = Position(2281.18f, -5300.47f, 85.1761f, 1.59344f);
Position const orbaz_bloodbane_fleeing_battle = Position(2210.65f, -5254.59f, 79.5469f, 2.48858f);

//battle lost
Position const koltira_to_lights_hope_battle_lost = Position(2284.99f, -5278.16f, 82.1574f, 4.67614f);
Position const thassarian_to_lights_hope_battle_lost = Position(2277.75f, -5277.93f, 82.1426f, 4.68007f);
Position const darion_to_lights_hope_battle_lost = Position(2281.15f, -5282.14f, 82.4568f, 4.69969f);

Position const maxwell_to_lights_hope_battle_lost = Position(2285.01f, -5304.13f, 86.0875f, 1.7529f);
Position const korfax_to_lights_hope_battle_lost = Position(2277.2f, -5304.67f, 85.7383f, 1.36806f);
Position const leonid_to_lights_hope_battle_lost = Position(2278.77f, -5308.91f, 86.7747f, 1.54477f);
Position const nicholas_to_lights_hope_battle_lost = Position(2283.4f, -5308.96f, 87.1077f, 1.59975f);
Position const eligor_to_lights_hope_battle_lost = Position(2281.3f, -5313.31f, 87.8565f, 1.59975f);
Position const rayne_to_lights_hope_battle_lost = Position(2277.11f, -5313.62f, 87.614f, 1.50943f);
Position const rimblat_to_lights_hope_battle_lost = Position(2286.4f, -5312.88f, 88.1011f, 1.78824f);
Position const defender_of_the_light_to_lights_hope_battle_lost[] =
{
    {2275.07f, -5274.45f, 81.8412f, 5.45368f},
    {2272.73f, -5282.56f, 82.1773f, 0.0265655f},
    {2274.12f, -5289.82f, 82.8114f, 0.800183f},
    {2272.96f, -5286.58f, 82.4221f, 0.474243f},
    {2273.54f, -5278.49f, 82.0304f, 5.80317f},
    {2287.77f, -5290.0f, 83.2324f, 2.37492f},
    {2287.61f, -5274.83f, 81.947f, 3.96535f},
    {2289.5f, -5283.07f, 82.2357f, 3.0857f},
    {2288.92f, -5278.9f, 82.0701f, 3.5216f},
    {2288.86f, -5286.7f, 82.6186f, 2.68515f},
    {2271.35f, -5274.97f, 81.733f, 5.66731f},
    {2269.54f, -5279.66f, 81.9054f, 6.03252f},
    {2269.18f, -5285.67f, 82.0605f, 0.299108f},
    {2270.09f, -5289.7f, 82.343f, 0.589706f},
    {2291.0f, -5290.12f, 82.4368f, 2.47625f},
    {2292.4f, -5285.75f, 82.2662f, 2.84931f},
    {2292.77f, -5280.25f, 81.9502f, 3.35197f},
    {2291.46f, -5275.46f, 81.8674f, 3.73288f},
    {2276.84f, -5294.59f, 83.7321f, 1.24318f},
    {2285.24f, -5295.01f, 84.2269f, 1.87542f}
};

//flashback
Position const young_darion_to_alexandros_mograine = Position(2281.07f, -5263.99f, 81.2432f, 1.52483f);
Position const tirion_to_near_darion = Position(2284.13f, -5286.73f, 82.8725f, 1.6481f);
Position const darion_kockback_position = Position(2256.29f, -5303.07f, 82.1674f, 0.725273f);
Position const lich_king_closer_to_tirion = Position(2281.02f, -5267.11f, 81.559f, 4.71749f);
Position const tirion_to_darion_to_heal = Position(2256.67f, -5300.09f, 82.1679f, 4.67224f);
Position const tirion_to_speech_position = Position(2273.65f, -5286.43f, 82.4756f, 3.85934f);
Position const maxwell_final_position = Position(2274.01f, -5315.6f, 87.4813f, 1.97437f);
Position const korfax_final_position = Position(2277.21f, -5314.99f, 87.9423f, 2.09611f);
Position const leonid_final_position = Position(2279.68f, -5313.48f, 87.7679f, 2.21392f);
Position const nicholas_final_position = Position(2282.42f, -5311.81f, 87.6537f, 2.39456f);
Position const eligor_final_position = Position(2284.46f, -5309.27f, 87.1952f, 2.51237f);
Position const rayne_final_position = Position(2279.77f, -5317.56f, 88.4596f, 2.19821f);
Position const rimblat_final_position = Position(2282.71f, -5315.62f, 88.3116f, 2.28853f);

//game object spawn locations
Position const holy_lightning_spawn_locations[] =
{
    {2334.93f, -5280.21f, 81.7803f, 5.36098f},
    {2326.46f, -5254.79f, 84.1246f, 2.05838f},
    {2300.05f, -5238.88f, 84.3055f, 2.60031f},
    {2275.25f, -5236.93f, 80.5219f, 4.76015f},
    {2254.42f, -5259.98f, 76.8126f, 5.62802f},
    {2239.02f, -5278.35f, 79.4279f, 5.7144f},
    {2249.52f, -5303.4f, 82.1678f, 5.70261f},
    {2262.74f, -5286.49f, 81.7722f, 0.507199f},
    {2289.39f, -5280.12f, 82.0977f, 0.0870115f},
    {2310.91f, -5301.19f, 81.9969f, 4.96434f},
    {2282.05f, -5312.41f, 87.7435f, 4.59913f},
    {2251.55f, -5330.37f, 82.8659f, 4.19858f},
    {2273.86f, -5337.3f, 87.9812f, 0.727112f},
    {2341.27f, -5312.86f, 83.236f, 2.91445f},
    {2321.51f, -5328.81f, 81.9967f, 1.50858f}
};

enum darion_mograine
{
    //required players to queue for the event before it automatically starts
    EVENT_REQUIREMENT_PLAYERS = 1,
    //gossip event action for a player queuing for the event
    EVENT_GOSSIP_ACTION_PLAYER_QUEUE = 1001,
    EVENT_GOSSIP_ACTION_DEBUG_FOR_COMBAT_TEST = 1002,
    EVENT_GOSSIP_TEXTID_PLAYER_NOT_REGISTERED = 60000,
    EVENT_GOSSIP_TEXTID_PLAYER_REGISTERED = 60001,
    EVENT_GOSSIP_TEXTID_EVENT_DONE = 60002,

    //phase darion starts in where he waits for an amount of players equal to EVENT_REQUIREMENT_PLAYERS to queue for the event by talking to him and saying "I am ready" before going to the next phase
    PHASE_WAITING_FOR_PLAYERS = 0,
    PHASE_WAITING_FOR_BATTLE = 1,
    PHASE_OPENING_SCENE = 2,
    PHASE_CHARGE_INTO_BATTLE = 3,
    PHASE_IN_BATTLE = 4,
    PHASE_BATTLE_LOST = 5,
    PHASE_FLASH_BACK = 6,
    PHASE_EVENT_DONE = 7,

    //scripted events
    //waiting for players phase
    SCRIPT_PHASE_WAITING_FOR_BATTLE_UPDATE_EVENT_COUNTDOWN_WORLDSTATE = 1,
    SCRIPT_PHASE_WAITING_FOR_BATTLE_TALK_1 = 2,
    SCRIPT_PHASE_WAITING_FOR_BATTLE_TALK_2 = 3,
    SCRIPT_PHASE_WAITING_FOR_BATTLE_TALK_3 = 4,
    SCRIPT_PHASE_WAITING_FOR_BATTLE_TO_PHASE_OPENING_SCENE = 5,

    //opening scene phase
    SCRIPT_PHASE_OPENING_SCENE_TALK_1 = 6,
    SCRIPT_PHASE_OPENING_SCENE_TALK_2 = 7,
    SCRIPT_PHASE_OPENING_SCENE_SUMMON = 8,
    SCRIPT_PHASE_OPENING_SCENE_SCRIPTED_SUMMONS_ATTACK_ANIMATION = 9,
    SCRIPT_PHASE_OPENING_SCENE_SCRIPTED_SUMMONS_COMPLETE_SPAWN = 10,
    SCRIPT_PHASE_OPENING_SCENE_TALK_3 = 11,
    SCRIPT_PHASE_OPENING_SCENE_SCOURGE_ROAR = 12,
    SCRIPT_PHASE_OPENING_SCENE_TO_PHASE_CHARGE_INTO_BATTLE = 13,

    //charging into battle phase
    SCRIPT_PHASE_CHARGING_INTO_BATTLE_TO_IN_BATTLE = 14,

    //in battle phase
    SCRIPT_PHASE_IN_BATTLE_DARION_TALK = 15,
    SCRIPT_PHASE_IN_BATTLE_CAST_DEATHS_EMBRACE = 16,
    SCRIPT_PHASE_IN_BATTLE_CAST_ICY_TOUCH = 17,
    SCRIPT_PHASE_IN_BATTLE_CAST_UNHOLY_BLIGHT = 18,
    SCRIPT_PHASE_IN_BATTLE_CAST_ANTI_MAGIC_ZONE = 19,
    SCRIPT_PHASE_IN_BATTLE_SUMMON_RAMPAGING_ABOMINATIONS = 20,
    SCRIPT_PHASE_IN_BATTLE_START_LOSING_BATTLE = 21,
    SCRIPT_PHASE_IN_BATTLE_KILL_ALL_SCOURGE_UNITS = 22,
    SCRIPT_PHASE_IN_BATTLE_ORBAZ_FLEES = 23,
    SCRIPT_PHASE_IN_BATTLE_ORBAZ_DESPAWN = 24,
    SCRIPT_PHASE_IN_BATTLE_TIRION_MOVE_TO_LIGHTS_HOPE = 25,
    SCRIPT_PHASE_IN_BATTLE_TO_BATTLE_LOST = 26,

    //battle lost phase
    SCRIPT_PHASE_BATTLE_LOST_SETUP_NPCS = 27,
    SCRIPT_PHASE_BATTLE_LOST_TIRION_TALK_1 = 28,
    SCRIPT_PHASE_BATTLE_LOST_EVERYONE_MOVE_TO_POSITIONS = 29,
    SCRIPT_PHASE_BATTLE_LOST_DARION_TALK_1 = 30,
    SCRIPT_PHASE_BATTLE_LOST_DKS_STAND_DOWN = 31,
    SCRIPT_PHASE_BATTLE_LOST_DARION_KNEEL = 32,
    SCRIPT_PHASE_BATTLE_LOST_DKS_KNEEL = 33,
    SCRIPT_PHASE_BATTLE_LOST_TIRON_TALK_2 = 34,
    SCRIPT_PHASE_BATTLE_LOST_TIRON_TALK_3 = 35,
    SCRIPT_PHASE_BATTLE_LOST_TIRON_TALK_4 = 36,
    SCRIPT_PHASE_BATTLE_LOST_DIRION_TALK_2 = 37,
    SCRIPT_PHASE_BATTLE_LOST_DIRION_POINT_AT_TIRION = 38,
    SCRIPT_PHASE_BATTLE_LOST_TO_PHASE_FLASH_BACK = 39,

    //flashback phase
    SCRIPT_PHASE_FLASH_BACK_ALEXANDROS_TALK_1 = 40,
    SCRIPT_PHASE_FLASH_BACK_DARION_TURN_TO_FACE_ALEXANDROS = 41,
    SCRIPT_PHASE_FLASH_BACK_DARION_TALK_1 = 42,
    SCRIPT_PHASE_FLASH_BACK_SPAWN_YOUNG_DARION = 43,
    SCRIPT_PHASE_FLASH_BACK_DARION_TALK_2 = 44,
    SCRIPT_PHASE_FLASH_BACK_YOUNG_DARION_TALK_1 = 45,
    SCRIPT_PHASE_FLASH_BACK_YOUNG_DARION_RUN_TO_ALEXANDROS = 46,
    SCRIPT_PHASE_FLASH_BACK_YOUNG_DARION_TALK_2 = 47,
    SCRIPT_PHASE_FLASH_BACK_YOUNG_DARION_TALK_3 = 48,
    SCRIPT_PHASE_FLASH_BACK_ALEXANDROS_TALK_2 = 49,
    SCRIPT_PHASE_FLASH_BACK_YOUNG_DARION_TALK_4 = 50,
    SCRIPT_PHASE_FLASH_BACK_ALEXANDROS_TALK_3 = 51,
    SCRIPT_PHASE_FLASH_BACK_TIRION_WALK_NEAR_DARION = 52,
    SCRIPT_PHASE_FLASH_BACK_YOUNG_DARION_TALK_5 = 53,
    SCRIPT_PHASE_FLASH_BACK_ALEXANDROS_TALK_4 = 54,
    SCRIPT_PHASE_FLASH_BACK_ALEXANDROS_TALK_5 = 55,
    SCRIPT_PHASE_FLASH_BACK_LICH_KING_SPAWN = 56,
    SCRIPT_PHASE_FLASH_BACK_LICH_KING_TALK_1 = 57,
    SCRIPT_PHASE_FLASH_BACK_LICH_KING_TALK_2 = 58,
    SCRIPT_PHASE_FLASH_BACK_ALEXANDROS_DESPAWN = 59,
    SCRIPT_PHASE_FLASH_BACK_DARION_STAND_UP = 60,
    SCRIPT_PHASE_FLASH_BACK_DARION_TALK_3 = 61,
    SCRIPT_PHASE_FLASH_BACK_LICH_KING_WALK_FORWARD = 62,
    SCRIPT_PHASE_FLASH_BACK_DARION_CHARGE_AT_LICH_KING = 63,
    SCRIPT_PHASE_FLASH_BACK_DARION_KNOCKED_BACK = 64,
    SCRIPT_PHASE_FLASH_BACK_DARION_KNEEL_AFTER_KNOCKBACK = 65,
    SCRIPT_PHASE_FLASH_BACK_TIRION_TALK_1 = 66,
    SCRIPT_PHASE_FLASH_BACK_LICH_KING_LAUGH = 67,
    SCRIPT_PHASE_FLASH_BACK_LICH_KING_TALK_3 = 68,
    SCRIPT_PHASE_FLASH_BACK_LICH_KING_POINT_AT_TIRION = 69,
    SCRIPT_PHASE_FLASH_BACK_LICH_KING_TALK_4 = 70,
    SCRIPT_PHASE_FLASH_BACK_LICH_KING_DRAIN_TIRION = 71,
    SCRIPT_PHASE_FLASH_BACK_ALL_DAWN_ATTACK_LICH_KING = 72,
    SCRIPT_PHASE_FLASH_BACK_LICH_CAST_APOCOLYPSE_ON_ALL_DAWN = 73,
    SCRIPT_PHASE_FLASH_BACK_ALL_DAWN_KNOCKED_DOWN = 74,
    SCRIPT_PHASE_FLASH_BACK_DARION_TALK_4 = 75,
    SCRIPT_PHASE_FLASH_BACK_DARION_TALK_5 = 76,
    SCRIPT_PHASE_FLASH_BACK_DARION_THROW_ASHBRINGER_AT_TIRION = 77,
    SCRIPT_PHASE_FLASH_BACK_DARION_COLLAPSE = 78,
    SCRIPT_PHASE_FLASH_BACK_TIRION_PURIFIES_ASHBRINGER = 79,
    SCRIPT_PHASE_FLASH_BACK_TIRION_EQUIPS_ASHBRINGER = 80,
    SCRIPT_PHASE_FLASH_BACK_TIRION_TALK_2 = 81,
    SCRIPT_PHASE_FLASH_BACK_LICH_KING_TALK_5 = 82,
    SCRIPT_PHASE_FLASH_BACK_TIRION_TALK_3 = 83,
    SCRIPT_PHASE_FLASH_BACK_TIRION_CHARGE_AT_LICH_KING = 84,
    SCRIPT_PHASE_FLASH_BACK_TIRION_LAND_FROM_CHARGE = 85,
    SCRIPT_PHASE_FLASH_BACK_LICH_KING_TALK_6 = 86,
    SCRIPT_PHASE_FLASH_BACK_LICH_KING_TALK_7 = 87,
    SCRIPT_PHASE_FLASH_BACK_LICH_KING_TALK_8 = 88,
    SCRIPT_PHASE_FLASH_BACK_LICH_KING_CAST_DESPAWN_SPELL = 89,
    SCRIPT_PHASE_FLASH_BACK_LICH_KING_DESPAWN = 90,
    SCRIPT_PHASE_FLASH_BACK_TIRION_WALK_TO_DARION = 91,
    SCRIPT_PHASE_FLASH_BACK_TIRION_CAST_LAY_ON_HANDS_ON_DARION = 92,
    SCRIPT_PHASE_FLASH_BACK_TIRION_TALK_4 = 93,
    SCRIPT_PHASE_FLASH_BACK_TIRION_WALK_AWAY_FROM_DARION = 94,
    SCRIPT_PHASE_FLASH_BACK_TIRION_TALK_5 = 95,
    SCRIPT_PHASE_FLASH_BACK_TIRION_TALK_6 = 96,
    SCRIPT_PHASE_FLASH_BACK_TIRION_TALK_7 = 97,
    SCRIPT_PHASE_FLASH_BACK_TIRION_TALK_8 = 98,
    SCRIPT_PHASE_FLASH_BACK_TIRION_TALK_9 = 99,
    SCRIPT_PHASE_FLASH_BACK_TIRION_TALK_10 = 100,
    SCRIPT_PHASE_FLASH_BACK_TIRION_TALK_11 = 101,
    SCRIPT_PHASE_FLASH_BACK_DARION_GET_UP = 102,
    SCRIPT_PHASE_FLASH_BACK_DARION_TALK_6 = 103,
    SCRIPT_PHASE_FLASH_BACK_TO_PHASE_EVENT_DONE = 104,

    //other
    SCRIPT_IN_BATTLE_UPDATE_TARGET_LIST = 105,
    SCRIPT_PHASE_ANY_SET_WEATHER_TO_RAINING_REPEATING = 106,
    SCRIPT_PHASE_ANY_DESPAWN_SUMMON_CORPSE = 107,
    SCRIPT_PHASE_ANY_RESPAWN = 108,

    //combat timers
    TIMER_HIGHLORD_DARION_MOGRAINE_DEATHS_TALK_FIRST = 15,
    TIMER_HIGHLORD_DARION_MOGRAINE_DEATHS_TALK_REPEAT = 15,
    TIMER_HIGHLORD_DARION_MOGRAINE_DEATHS_EMBRACE_FIRST = 10,
    TIMER_HIGHLORD_DARION_MOGRAINE_DEATHS_EMBRACE_REPEAT = 20,
    TIMER_HIGHLORD_DARION_MOGRAINE_ICY_TOUCH_FIRST = 5,
    TIMER_HIGHLORD_DARION_MOGRAINE_ICY_TOUCH_REPEAT = 5,
    TIMER_HIGHLORD_DARION_MOGRAINE_UNHOLY_BLIGHT_FIRST = 1,
    TIMER_HIGHLORD_DARION_MOGRAINE_UNHOLY_BLIGHT_REPEAT = 9,
    TIMER_HIGHLORD_DARION_MOGRAINE_ANTI_MAGIC_ZONE_FIRST = 15,
    TIMER_HIGHLORD_DARION_MOGRAINE_ANTI_MAGIC_ZONE_REPEAT = 20,
};

class npc_highlord_darion_mograine : public CreatureScript
{
    public:
        npc_highlord_darion_mograine() : CreatureScript("npc_highlord_darion_mograine") { }

        struct npc_highlord_darion_mograineAI : public ScriptedAI
        {
            //##attributes##
            //current phase darion is in
            uint32 current_phase;
            //list of players currently recognized as participating in the event
            std::list<Player*> playerList;
            //bools for tracking if certain creatures were spawned to safely know when to despawn them in despawnSummons
            bool koltira_spawned;
            bool orbaz_spawned;
            bool thassarian_spawned;
            bool flesh_behemoths_spawned;
            bool openening_scene_creatures_spawned;
            bool rampaging_abominations_spawned;
            bool lights_hope_creatures_spawned;
            bool young_mograine_spawned;
            bool alexandros_spawned;
            bool lich_king_spawned;
            bool tirion_spawned;
            bool worldstates_reset;
            bool corpses_despawned;
            bool holy_lightning_spawned;
            bool light_of_dawn_spawned;
            //timed event notifier
            EventMap events;
            //summoned scourge units
            TempSummon *flesh_behemoths[NUMBER_FLESH_BEHEMOTH];
            TempSummon *rampaging_abominations[NUMBER_RAMPAGING_ABOMINATION];
            TempSummon *warrior_of_the_frozen_wastes[NUMBER_WARRIOR_OF_THE_FROZEN_WASTES];
            TempSummon *volatile_ghouls[NUMBER_VOLATILE_GHOUL];
            TempSummon *koltira;
            TempSummon *orbaz;
            TempSummon *thassarian;
            //summoned lights hope units
            TempSummon *defenders_of_the_light[NUMBER_DEFENDER_OF_THE_LIGHT];
            TempSummon *maxwell;
            TempSummon *korfax;
            TempSummon *leonid;
            TempSummon *nicholas;
            TempSummon *eligor;
            TempSummon *rayne;
            TempSummon *rimblat;
            //outro summoned units / game objects
            TempSummon *alexandros;
            TempSummon *young_mograine;
            TempSummon *lich_king;
            TempSummon *tirion;
            GameObject *holy_lightnings_horizontal[NUMBER_HOLY_LIGHTNING];
            GameObject *holy_lightnings_vertical[NUMBER_HOLY_LIGHTNING];
            GameObject *light_of_dawn;
            //list used to hold scripted summons such as the volatile ghouls with a special scripted spawn and whatnot
            std::list<TempSummon*> scriptedSummonList_for_attack_animation;
            std::list<TempSummon*> scriptedSummonList_for_spawn_cleanup;
            //used to hold pointers to summons that need their corpses despawned on a timer
            std::list<Creature*> corpse_cleanup_list;
            uint32 remaining_scourge;
            uint32 remaining_argent_dawn;
            uint32 event_countdown_remaining_time;
            //combat AI stuff
            //creature's creature_template id
            uint32 entry;
            //range at which the creature will aquire targets in
            float targetAquisitionRange;
            //holds all targets within targetAquisitionRange aquired through updateInCombatWithList()
            std::list<Unit*> targetList;
            //used to hold target info for scripts
            Unit *tempTarget1;
            //used to determine if the unit has been out of combat without re-entering combat
            bool first_outOfCombat_recent;
            //used to determine if the unit has been in combat without recently leaving combat
            bool first_inCombat_recent;
            //used to determine if the unit has entered combat at all
            bool first_inCombat_ever;
            //used to determine if the unit is casting
            bool casting;

            //combat AI functions begin
            //used by updateCombatList for creatures to shorten code
            void pushBackEligibleTargetsFromList(std::list<Creature*> &creatureList)
            {
                if (!creatureList.empty())
                {
                    std::list<Creature*>::iterator cItr;
                    Creature *cItrTarget = nullptr;

                    for (cItr = creatureList.begin(); cItr != creatureList.end(); ++cItr)
                    {
                        cItrTarget = (*cItr);
                        if ((cItrTarget->GetReactState() == REACT_AGGRESSIVE) && cItrTarget->IsAlive() && cItrTarget->IsInWorld())
                        {
                            //me->Say("Creature target found.", LANG_UNIVERSAL);
                            targetList.push_back(cItrTarget->ToUnit());
                        }
                    }
                }
            }

            //used by updateCombatList for players to shorten code
            void pushBackEligibleTargetsFromList(std::list<Player*> &playerList)
            {
                if (!playerList.empty())
                {
                    //me->Say("Player target found.", LANG_UNIVERSAL);
                    std::list<Player*>::iterator pItr;
                    Player *pItrTarget = nullptr;

                    for (pItr = playerList.begin(); pItr != playerList.end(); ++pItr)
                    {
                        pItrTarget = (*pItr);

                        if (me->IsHostileTo(pItrTarget) && pItrTarget->IsAlive() && pItrTarget->IsInWorld())
                        {
                            //me->Say("Player target found.", LANG_UNIVERSAL);
                            targetList.push_back(pItrTarget->ToUnit());
                        }
                    }
                }
            }

            //gets all creatures of the proper ids for their corresponding faction (scourge or dawn)
            //within targetAquisitionRange and then adds them to targetList and sets the creature in combat with all of them
            void updateInCombatWithList(void)
            {
                //me->Say("updateInCombatWithList() called.", LANG_UNIVERSAL);
                targetList.clear();

                //define individual target lists
                std::list<Creature*> defenderOfTheLightList = std::list<Creature*>();
                std::list<Creature*> maxwellList = std::list<Creature*>();
                std::list<Creature*> korfaxList = std::list<Creature*>();
                std::list<Creature*> leonidList = std::list<Creature*>();
                std::list<Creature*> nicholasList = std::list<Creature*>();
                std::list<Creature*> eligorList = std::list<Creature*>();
                std::list<Creature*> rayneList = std::list<Creature*>();
                std::list<Creature*> rimblatList = std::list<Creature*>();

                //populate individual target lists
                me->GetCreatureListWithEntryInGrid(defenderOfTheLightList, ID_DEFENDER_OF_THE_LIGHT, targetAquisitionRange);
                me->GetCreatureListWithEntryInGrid(maxwellList, ID_LORD_MAXWELL_TYROSUS, targetAquisitionRange);
                me->GetCreatureListWithEntryInGrid(korfaxList, ID_KORFAX_CHAMPION_OF_THE_LIGHT, targetAquisitionRange);
                me->GetCreatureListWithEntryInGrid(leonidList, ID_LEONID_BARTHALOMEW_THE_REVERED, targetAquisitionRange);
                me->GetCreatureListWithEntryInGrid(nicholasList, ID_DUKE_NICHOLAS_ZVERENHOFF, targetAquisitionRange);
                me->GetCreatureListWithEntryInGrid(eligorList, ID_COMMANDER_ELIGOR_DAWNBRINGER, targetAquisitionRange);
                me->GetCreatureListWithEntryInGrid(rayneList, ID_RAYNE, targetAquisitionRange);
                me->GetCreatureListWithEntryInGrid(rimblatList, ID_RIMBLAT_EARTHSHATTER, targetAquisitionRange);

                //combine all target lists into targetList based on eligible for combat criteria
                pushBackEligibleTargetsFromList(defenderOfTheLightList);
                pushBackEligibleTargetsFromList(maxwellList);
                pushBackEligibleTargetsFromList(korfaxList);
                pushBackEligibleTargetsFromList(leonidList);
                pushBackEligibleTargetsFromList(nicholasList);
                pushBackEligibleTargetsFromList(eligorList);
                pushBackEligibleTargetsFromList(rayneList);
                pushBackEligibleTargetsFromList(rimblatList);

                //handle hostile players
                std::list<Player*> hostilePlayerList = std::list<Player*>();
                me->GetPlayerListInGrid(hostilePlayerList, targetAquisitionRange);
                pushBackEligibleTargetsFromList(hostilePlayerList);

                //set creature in combat with all targets
                if (!targetList.empty())
                {
                    for (std::list<Unit*>::iterator itr = targetList.begin(); itr != targetList.end(); ++itr)
                    {
                        //me->Say("Set in combat with target.", LANG_UNIVERSAL);
                        me->GetCombatManager().SetInCombatWith(*itr);
                    }
                }
            }
            //combat AI functions end

            //called when darion is created
            void spawn_initialize(void)
            {
                //assign current phase on creation
                current_phase = PHASE_WAITING_FOR_PLAYERS;
                //summon flesh behemoths and store them in the flesh_behemoths pointer array
                for (unsigned int x = 0; x < NUMBER_FLESH_BEHEMOTH; x++)
                {
                    flesh_behemoths[x] = me->SummonCreature(ID_FLESH_BEHEMOTH, Spawn_Positions_Flesh_Behemoth[x], TEMPSUMMON_MANUAL_DESPAWN);
                }
                //summon koltira
                koltira = me->SummonCreature(ID_KOLTIRA_DEATHWEAVER, Spawn_Positions_Koltira_Deathweaver, TEMPSUMMON_MANUAL_DESPAWN);
                //summon orbaz
                orbaz = me->SummonCreature(ID_ORBAZ_BLOODBANE, Spawn_Positions_Orbaz_Bloodbane, TEMPSUMMON_MANUAL_DESPAWN);
                //summon thassarian
                thassarian = me->SummonCreature(ID_THASSARIAN, Spawn_Positions_Thassarian, TEMPSUMMON_MANUAL_DESPAWN);

                koltira_spawned = true;
                orbaz_spawned = true;
                thassarian_spawned = true;
                flesh_behemoths_spawned = true;
                //me->Say("initialized", LANG_UNIVERSAL);
            }

            void despawnCorpseOfSummon(void)
            {
                if (!(corpse_cleanup_list.empty()))
                {
                    std::list<Creature*>::iterator itr = corpse_cleanup_list.begin();
                    Creature *SummonCorpseForDespawn = (*itr);

                    if (SummonCorpseForDespawn->IsInWorld())
                    {
                        SummonCorpseForDespawn->DespawnOrUnsummon();
                    }

                    corpse_cleanup_list.erase(itr);
                    SummonCorpseForDespawn = nullptr;
                }
                else
                {
                    //me->Say("true", LANG_UNIVERSAL);
                }
            }

            //despawns all possible summoned units
            void despawnSummons(void)
            {
                //lights hope creatures
                if (lights_hope_creatures_spawned)
                {
                    //defenders of the light
                    for (unsigned int x = 0; x < NUMBER_DEFENDER_OF_THE_LIGHT; x++)
                    {
                        if (defenders_of_the_light[x])
                        {
                            defenders_of_the_light[x]->DespawnOrUnsummon();
                            defenders_of_the_light[x] = nullptr;
                        }
                    }

                    //maxwell
                    maxwell->DespawnOrUnsummon();
                    maxwell = nullptr;
                    //korfax
                    korfax->DespawnOrUnsummon();
                    korfax = nullptr;
                    //leonid
                    leonid->DespawnOrUnsummon();
                    leonid = nullptr;
                    //nicholas
                    nicholas->DespawnOrUnsummon();
                    nicholas = nullptr;
                    //eligor
                    eligor->DespawnOrUnsummon();
                    eligor = nullptr;
                    //rayne
                    rayne->DespawnOrUnsummon();
                    rayne = nullptr;
                    //rimblat
                    rimblat->DespawnOrUnsummon();
                    rimblat = nullptr;
                }

                //rampaging abominations
                if (rampaging_abominations_spawned)
                {
                    for (unsigned int x = 0; x < NUMBER_RAMPAGING_ABOMINATION; x++)
                    {
                        if (rampaging_abominations[x])
                        {
                            rampaging_abominations[x]->DespawnOrUnsummon();
                            rampaging_abominations[x] = nullptr;
                        }
                    }
                }

                //opening scene creatures
                //warriors of the frozen wastes
                if (openening_scene_creatures_spawned)
                {
                    for (unsigned int x = 0; x < NUMBER_WARRIOR_OF_THE_FROZEN_WASTES; x++)
                    {
                        if (warrior_of_the_frozen_wastes[x])
                        {
                            warrior_of_the_frozen_wastes[x]->DespawnOrUnsummon();
                            warrior_of_the_frozen_wastes[x] = nullptr;
                        }
                    }


                    //volatile ghouls
                    for (unsigned int x = 0; x < NUMBER_VOLATILE_GHOUL; x++)
                    {
                        if (volatile_ghouls[x])
                        {
                            volatile_ghouls[x]->DespawnOrUnsummon();
                            volatile_ghouls[x] = nullptr;
                        }
                    }
                }

                //base creatures
                if (flesh_behemoths_spawned)
                {
                    //flesh behemoths
                    for (unsigned int x = 0; x < NUMBER_FLESH_BEHEMOTH; x++)
                    {
                        if (flesh_behemoths[x])
                        {
                            flesh_behemoths[x]->DespawnOrUnsummon();
                            flesh_behemoths[x] = nullptr;
                        }
                    }
                }

                if (koltira_spawned)
                {
                    //koltira
                    if (koltira)
                    {
                        koltira->DespawnOrUnsummon();
                        koltira = nullptr;
                    }
                }

                if (orbaz_spawned)
                {
                    //orbas
                    if (orbaz)
                    {
                        orbaz->DespawnOrUnsummon();
                        orbaz = nullptr;
                    }
                }

                if (thassarian_spawned)
                {
                    //thassarian
                    if (thassarian)
                    {
                        thassarian->DespawnOrUnsummon();
                        thassarian = nullptr;
                    }
                }

                if (young_mograine_spawned)
                {
                    //young mograine
                    if (young_mograine)
                    {
                        young_mograine->DespawnOrUnsummon();
                        young_mograine = nullptr;
                    }
                }

                if (alexandros_spawned)
                {
                    //alexandros
                    if (alexandros)
                    {
                        alexandros->DespawnOrUnsummon();
                        alexandros = nullptr;
                    }
                }

                if (lich_king_spawned)
                {
                    //lich king
                    if (lich_king)
                    {
                        lich_king->DespawnOrUnsummon();
                        lich_king = nullptr;
                    }
                }

                if (tirion_spawned)
                {
                    //tirion
                    if (tirion)
                    {
                        tirion->DespawnOrUnsummon();
                        tirion = nullptr;
                    }
                }

                if (holy_lightning_spawned)
                {
                    //holy lightning horizontal objects
                    for (unsigned int x = 0; x < NUMBER_HOLY_LIGHTNING; x++)
                    {
                        if (holy_lightnings_horizontal[x])
                        {
                            holy_lightnings_horizontal[x]->DespawnOrUnsummon();
                            holy_lightnings_horizontal[x] = nullptr;
                        }
                    }

                    //holy lightning vertical objects
                    for (unsigned int x = 0; x < NUMBER_HOLY_LIGHTNING; x++)
                    {
                        if (holy_lightnings_vertical[x])
                        {
                            holy_lightnings_vertical[x]->DespawnOrUnsummon();
                            holy_lightnings_vertical[x] = nullptr;
                        }
                    }
                }

                if (light_of_dawn_spawned)
                {
                    light_of_dawn->DespawnOrUnsummon();
                    light_of_dawn = nullptr;
                }

                //despawn corpses
                if (!corpses_despawned)
                {
                    if (!corpse_cleanup_list.empty())
                    {
                        //me->Say("true", LANG_UNIVERSAL);
                        for (unsigned int x = 0; x < corpse_cleanup_list.size(); x++)
                        {
                            despawnCorpseOfSummon();
                            //me->Say("corpse despawned", LANG_UNIVERSAL);
                        }
                    }
                    else
                    {
                        //me->Say("false", LANG_UNIVERSAL);
                    }
                }

                //this is here to make sequential calls do nothing when referenced by the same AI struct
                koltira_spawned = false;
                orbaz_spawned = false;
                thassarian_spawned = false;
                flesh_behemoths_spawned = false;
                openening_scene_creatures_spawned = false;
                rampaging_abominations_spawned = false;
                lights_hope_creatures_spawned = false;
                young_mograine_spawned = false;
                alexandros_spawned = false;
                lich_king_spawned = false;
                tirion_spawned = false;
                holy_lightning_spawned = false;
                light_of_dawn_spawned = false;
                corpses_despawned = true;
            }

            void updateWorldStateForPlayers(uint32 worlsState_id, uint32 worlsState_state)
            {
                Map *map = me->GetMap();

                Map::PlayerList const &players = map->GetPlayers();

                if (!players.isEmpty())
                {
                    for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
                    {
                        Player *player = itr->GetSource();
                        player->SendUpdateWorldState(worlsState_id, worlsState_state);
                    }
                }
            }

            //resets all worldstates for players
            void resetWorldStates(void)
            {
                if (!worldstates_reset)
                {
                    updateWorldStateForPlayers(WORLD_STATE_COUNTDOWN_TIME, 0);
                    updateWorldStateForPlayers(WORLD_STATE_COUNTDOWN_ENABLE, 0);
                    updateWorldStateForPlayers(WORLD_STATE_EVENT_BEGIN_ENABLE, 0);
                    updateWorldStateForPlayers(WORLD_STATE_SOLDIERS_ENABLE, 0);
                    updateWorldStateForPlayers(WORLD_STATE_SCOURGE_COUNT, 0);
                    updateWorldStateForPlayers(WORLD_STATE_DEFENDERS_COUNT, 0);
                    setZoneWeatherToRaining(false);
                }

                worldstates_reset = true;
            }

            //used to summon ghouls and warrior as they have special scripted spawns that need to happen before they are ready to fight
            //for type:
            //true = warrior of the frozen wastes
            //false = ghoul
            //summonSpawnLocation is just the position that the ghoul / warrior should spawn at
            TempSummon *summon_Warrior_or_ghoul(bool type, Position const summonSpawnLocation)
            {
                //me->Say("summon warrior or ghoul called", LANG_UNIVERSAL);
                TempSummon *warriorOrGhoul = nullptr;

                //spawn in the warrior or ghoul at summonSpawnLocation
                if (type)
                {
                    warriorOrGhoul = me->SummonCreature(ID_WARRIOR_OF_THE_FROZEN_WASTES, summonSpawnLocation, TEMPSUMMON_MANUAL_DESPAWN);
                }
                else
                {
                    warriorOrGhoul = me->SummonCreature(ID_VOLATILE_GHOUL, summonSpawnLocation, TEMPSUMMON_MANUAL_DESPAWN);
                }

                //force the warrior to be rooted
                warriorOrGhoul->SetControlled(true, UNIT_STATE_ROOT);
                //cast the special birth animation spell on self
                warriorOrGhoul->CastSpell(warriorOrGhoul, SPELL_SCOURGE_MINION_BIRTH_EFFECT, CastSpellExtraArgs(true));
                //cast radial camera shake spell on self
                warriorOrGhoul->CastSpell(warriorOrGhoul, SPELL_PLAYER_CAMERA_SHAKE, CastSpellExtraArgs(true));
                //add the warrior to the scripted summons list for attack animation
                scriptedSummonList_for_attack_animation.push_back(warriorOrGhoul);
                //schedule event for darion to tell the warrior to do the attack animation after birth animation is done
                events.ScheduleEvent(SCRIPT_PHASE_OPENING_SCENE_SCRIPTED_SUMMONS_ATTACK_ANIMATION, 4s);

                return warriorOrGhoul;
            }

            //summon the warriors of the frozen wastes and volatile ghouls for the opening scene
            void summonUnits_OpeningScene(void)
            {
                //spawn in warriors of the frozen wastes
                for (unsigned int x = 0; x < NUMBER_WARRIOR_OF_THE_FROZEN_WASTES; x++)
                {
                    //spawn the warrior of the frozen wastes and add it to the warrior array
                    warrior_of_the_frozen_wastes[x] = summon_Warrior_or_ghoul(true, Spawn_Positions_Warrior_Of_The_Frozen_Wastes[x]);
                }

                //spawn in volatile ghouls
                for (unsigned int x = 0; x < NUMBER_VOLATILE_GHOUL; x++)
                {
                    //spawn the volatile ghouls and add the ghoul to the ghoul array
                    volatile_ghouls[x] = summon_Warrior_or_ghoul(false, Spawn_Positions_Volatile_Ghoul[x]);
                }

                openening_scene_creatures_spawned = true;
            }

            //tell the warrior and ghouls to do the attack animation after crawling out of the ground
            void doAttackAnimationForScriptedSummons(void)
            {
                std::list<TempSummon*>::iterator itr = scriptedSummonList_for_attack_animation.begin();
                TempSummon *scriptedSummon_for_attack_animation = (*itr);
                scriptedSummon_for_attack_animation->HandleEmoteCommand(EMOTE_ONESHOT_ATTACK1H);
                scriptedSummonList_for_attack_animation.erase(itr);
                //add the scripted summon to the scripted summons list for spawn cleanup
                scriptedSummonList_for_spawn_cleanup.push_back(scriptedSummon_for_attack_animation);
                //schedule event for darion to tell warrior to do spawn completion stuff like set proper flags, unroot and clean up the scripted summons list
                events.ScheduleEvent(SCRIPT_PHASE_OPENING_SCENE_SCRIPTED_SUMMONS_COMPLETE_SPAWN, 1s);
                scriptedSummon_for_attack_animation = nullptr;

                if (scriptedSummonList_for_attack_animation.empty())
                {
                    //me->Say("true", LANG_UNIVERSAL);
                }
            }

            //perform spawn finalization for warriors and ghouls and clean up the scripted summons list
            void finalizeSpawningAndCleanupScriptedSummons(void)
            {
                std::list<TempSummon*>::iterator itr = scriptedSummonList_for_spawn_cleanup.begin();
                TempSummon *scriptedSummon_for_spawn_cleanup = (*itr);
                scriptedSummon_for_spawn_cleanup->SetControlled(false, UNIT_STATE_ROOT);
                scriptedSummonList_for_spawn_cleanup.erase(itr);
                
                if (current_phase == PHASE_CHARGE_INTO_BATTLE || current_phase == PHASE_IN_BATTLE)
                {
                    scriptedSummon_for_spawn_cleanup->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_SILENCED | UNIT_FLAG_PACIFIED | UNIT_FLAG_NOT_SELECTABLE);
                    scriptedSummon_for_spawn_cleanup->SetReactState(REACT_AGGRESSIVE);
                    if (scriptedSummon_for_spawn_cleanup->IsAlive())
                    {
                        scriptedSummon_for_spawn_cleanup->GetMotionMaster()->MovePoint(0, scourgeMinion_respawn_battle, true);
                    }
                }
                else
                {
                    scriptedSummon_for_spawn_cleanup->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                }

                scriptedSummon_for_spawn_cleanup = nullptr;

                if (scriptedSummonList_for_spawn_cleanup.empty())
                {
                    //me->Say("true", LANG_UNIVERSAL);
                }
            }

            //cause all scourge units to do a roar emote or equivalent
            void summonedUnits_Roar_OpeningScene(void)
            {
                for (unsigned int x = 0; x < NUMBER_FLESH_BEHEMOTH; x++)
                {
                    TempSummon *flesh_behemoth = flesh_behemoths[x];
                    flesh_behemoth->HandleEmoteCommand(EMOTE_ONESHOT_BATTLE_ROAR);
                    flesh_behemoth = nullptr;
                }

                for (unsigned int x = 0; x < NUMBER_WARRIOR_OF_THE_FROZEN_WASTES; x++)
                {
                    TempSummon *warrior = warrior_of_the_frozen_wastes[x];
                    warrior->HandleEmoteCommand(EMOTE_ONESHOT_BATTLE_ROAR);
                    warrior = nullptr;
                }

                for (unsigned int x = 0; x < NUMBER_VOLATILE_GHOUL; x++)
                {
                    TempSummon *ghoul = volatile_ghouls[x];
                    ghoul->HandleEmoteCommand(EMOTE_ONESHOT_SPELL_CAST_OMNI);
                    ghoul = nullptr;
                }
            }

            //makes all summoned scourge units from the opening scene charge towards lights hope chapel
            void allScourgeUnitsMoveToLightsHope_charge_into_battle(void)
            {
                //tell darion and the three dks to move
                me->SetWalk(false);
                me->GetMotionMaster()->MovePoint(0, darion_to_lights_hope, true);
                koltira->SetWalk(false);
                koltira->GetMotionMaster()->MovePoint(0, darion_to_lights_hope, true);
                orbaz->SetWalk(false);
                orbaz->GetMotionMaster()->MovePoint(0, darion_to_lights_hope, true);
                thassarian->SetWalk(false);
                thassarian->GetMotionMaster()->MovePoint(0, darion_to_lights_hope, true);

                //tell flesh behemoths to move
                for (uint32 x = 0; x < NUMBER_FLESH_BEHEMOTH; x++)
                {
                    flesh_behemoths[x]->SetWalk(false);

                    if (x < (NUMBER_FLESH_BEHEMOTH / 2))
                    {
                        flesh_behemoths[x]->GetMotionMaster()->MovePoint(0, scourgeMinion_to_lights_hope_1, true);
                    }
                    else
                    {
                        flesh_behemoths[x]->GetMotionMaster()->MovePoint(0, scourgeMinion_to_lights_hope_2, true);
                    }
                }

                //tell warriors of the frozen wastes to move
                for (uint32 x = 0; x < NUMBER_WARRIOR_OF_THE_FROZEN_WASTES; x++)
                {
                    warrior_of_the_frozen_wastes[x]->SetWalk(false);

                    if (x < (NUMBER_WARRIOR_OF_THE_FROZEN_WASTES / 2))
                    {
                        warrior_of_the_frozen_wastes[x]->GetMotionMaster()->MovePoint(0, scourgeMinion_to_lights_hope_1, true);
                    }
                    else
                    {
                        warrior_of_the_frozen_wastes[x]->GetMotionMaster()->MovePoint(0, scourgeMinion_to_lights_hope_2, true);
                    }
                }

                //tell volatile ghoules to move
                for (uint32 x = 0; x < NUMBER_VOLATILE_GHOUL; x++)
                {
                    volatile_ghouls[x]->SetWalk(false);

                    if (x < (NUMBER_VOLATILE_GHOUL / 2))
                    {
                        volatile_ghouls[x]->GetMotionMaster()->MovePoint(0, scourgeMinion_to_lights_hope_1, true);
                    }
                    else
                    {
                        volatile_ghouls[x]->GetMotionMaster()->MovePoint(0, scourgeMinion_to_lights_hope_2, true);
                    }
                }
            }

            //summons all npcs that are defending lights hope chapel
            void summonAllLightsHopeNPCs(void)
            {
                //summon defenders of the light
                for (uint32 x = 0; x < NUMBER_DEFENDER_OF_THE_LIGHT; x++)
                {
                    TempSummon *defender_of_the_light = me->SummonCreature(ID_DEFENDER_OF_THE_LIGHT, defender_of_the_light_ready_location[x], TEMPSUMMON_MANUAL_DESPAWN);
                    defenders_of_the_light[x] = defender_of_the_light;
                    defender_of_the_light->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_READY2H);
                    defender_of_the_light->HandleEmoteCommand(EMOTE_STATE_READY2H);
                }

                //summon maxwell
                maxwell = me->SummonCreature(ID_LORD_MAXWELL_TYROSUS, Spawn_Positions_Lord_Maxwell_Tyrosus, TEMPSUMMON_MANUAL_DESPAWN);
                maxwell->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_READY2H);
                maxwell->HandleEmoteCommand(EMOTE_STATE_READY2H);
                //summon korfax
                korfax = me->SummonCreature(ID_KORFAX_CHAMPION_OF_THE_LIGHT, Spawn_Positions_Korfax_Champion_of_the_Light, TEMPSUMMON_MANUAL_DESPAWN);
                korfax->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_READY2H);
                korfax->HandleEmoteCommand(EMOTE_STATE_READY2H);
                //summon leonid
                leonid = me->SummonCreature(ID_LEONID_BARTHALOMEW_THE_REVERED, Spawn_Positions_Leonid_Barthalomew_the_Revered, TEMPSUMMON_MANUAL_DESPAWN);
                leonid->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_READY2H);
                leonid->HandleEmoteCommand(EMOTE_STATE_READY2H);
                //summon nicholas
                nicholas = me->SummonCreature(ID_DUKE_NICHOLAS_ZVERENHOFF, Spawn_Positions_Duke_Nicholas_Zverenhoff, TEMPSUMMON_MANUAL_DESPAWN);
                nicholas->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_READY2H);
                nicholas->HandleEmoteCommand(EMOTE_STATE_READY2H);
                //summon eligor
                eligor = me->SummonCreature(ID_COMMANDER_ELIGOR_DAWNBRINGER, Spawn_Positions_Commander_Eligor_Dawnbringer, TEMPSUMMON_MANUAL_DESPAWN);
                eligor->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_READY2H);
                eligor->HandleEmoteCommand(EMOTE_STATE_READY2H);
                //summon rayne
                rayne = me->SummonCreature(ID_RAYNE, Spawn_Positions_Rayne, TEMPSUMMON_MANUAL_DESPAWN);
                rayne->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_READY2H);
                rayne->HandleEmoteCommand(EMOTE_STATE_READY2H);
                //summon rimblat
                rimblat = me->SummonCreature(ID_RIMBLAT_EARTHSHATTER, Spawn_Positions_Rimblat_Earthshatter, TEMPSUMMON_MANUAL_DESPAWN);
                rimblat->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_READY2H);
                rimblat->HandleEmoteCommand(EMOTE_STATE_READY2H);

                lights_hope_creatures_spawned = true;
            }

            void allUnitsPrepareForCombat(void)
            {
                //tell darion and the three dks to enter agressive react state and remove combat inhibiting flags
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_SILENCED | UNIT_FLAG_PACIFIED);
                me->SetReactState(REACT_AGGRESSIVE);
                me->Dismount();
                koltira->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_SILENCED | UNIT_FLAG_PACIFIED);
                koltira->SetReactState(REACT_AGGRESSIVE);
                koltira->Dismount();
                orbaz->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_SILENCED | UNIT_FLAG_PACIFIED);
                orbaz->SetReactState(REACT_AGGRESSIVE);
                orbaz->Dismount();
                thassarian->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_SILENCED | UNIT_FLAG_PACIFIED);
                thassarian->SetReactState(REACT_AGGRESSIVE);
                thassarian->Dismount();

                //tell flesh behemoths to enter agressive react state and remove combat inhibiting flags
                for (uint32 x = 0; x < NUMBER_FLESH_BEHEMOTH; x++)
                {
                    flesh_behemoths[x]->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_SILENCED | UNIT_FLAG_PACIFIED);
                    flesh_behemoths[x]->SetReactState(REACT_AGGRESSIVE);
                }

                //tell warriors of the frozen wastes to enter agressive react state and remove combat inhibiting flags
                for (uint32 x = 0; x < NUMBER_WARRIOR_OF_THE_FROZEN_WASTES; x++)
                {
                    warrior_of_the_frozen_wastes[x]->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_SILENCED | UNIT_FLAG_PACIFIED);
                    warrior_of_the_frozen_wastes[x]->SetReactState(REACT_AGGRESSIVE);
                }

                //tell volatile ghoules to enter agressive react state and remove combat inhibiting flags
                for (uint32 x = 0; x < NUMBER_VOLATILE_GHOUL; x++)
                {
                    volatile_ghouls[x]->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_SILENCED | UNIT_FLAG_PACIFIED);
                    volatile_ghouls[x]->SetReactState(REACT_AGGRESSIVE);
                }

                //tell defenders of the light to enter agressive react state and remove combat inhibiting flags
                for (uint32 x = 0; x < NUMBER_DEFENDER_OF_THE_LIGHT; x++)
                {
                    defenders_of_the_light[x]->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_SILENCED | UNIT_FLAG_PACIFIED);
                    defenders_of_the_light[x]->SetReactState(REACT_AGGRESSIVE);
                }

                //tell maxwell to enter agressive react state and remove combat inhibiting flags
                maxwell->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_SILENCED | UNIT_FLAG_PACIFIED);
                maxwell->SetReactState(REACT_AGGRESSIVE);
                //tell korfax to enter agressive react state and remove combat inhibiting flags
                korfax->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_SILENCED | UNIT_FLAG_PACIFIED);
                korfax->SetReactState(REACT_AGGRESSIVE);
                //tell leonid to enter agressive react state and remove combat inhibiting flags
                leonid->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_SILENCED | UNIT_FLAG_PACIFIED);
                leonid->SetReactState(REACT_AGGRESSIVE);
                //tell nicholas to enter agressive react state and remove combat inhibiting flags
                nicholas->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_SILENCED | UNIT_FLAG_PACIFIED);
                nicholas->SetReactState(REACT_AGGRESSIVE);
                //tell eligor to enter agressive react state and remove combat inhibiting flags
                eligor->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_SILENCED | UNIT_FLAG_PACIFIED);
                eligor->SetReactState(REACT_AGGRESSIVE);
                //tell rayne to enter agressive react state and remove combat inhibiting flags
                rayne->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_SILENCED | UNIT_FLAG_PACIFIED);
                rayne->SetReactState(REACT_AGGRESSIVE);
                //tell rimblat to enter agressive react state and remove combat inhibiting flags
                rimblat->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_SILENCED | UNIT_FLAG_PACIFIED);
                rimblat->SetReactState(REACT_AGGRESSIVE);
            }

            //combat ai functions begin
            void highlordDarionMograine_cast_deathsEmbrace(void)
            {
                me->CastSpell(me, SPELL_DEATHS_EMBRACE);
                events.ScheduleEvent(SCRIPT_PHASE_IN_BATTLE_CAST_DEATHS_EMBRACE, (TIMER_HIGHLORD_DARION_MOGRAINE_DEATHS_EMBRACE_REPEAT * 1s));
            }

            void highlordDarionMograine_cast_icyTouch(void)
            {
                float distanceToTarget = me->GetDistance(me->GetVictim());

                if ((distanceToTarget >= 0) && (distanceToTarget <= 20) && !casting)
                {
                    me->CastSpell(me->GetVictim(), SPELL_ICY_TOUCH);
                    events.ScheduleEvent(SCRIPT_PHASE_IN_BATTLE_CAST_ICY_TOUCH, (TIMER_HIGHLORD_DARION_MOGRAINE_ICY_TOUCH_REPEAT * 1s));
                }
                else
                {
                    //me->Say("out of proper range for icy touch, rescheduling by 1s", LANG_UNIVERSAL);
                    events.ScheduleEvent(SCRIPT_PHASE_IN_BATTLE_CAST_ICY_TOUCH, 1s);
                }
            }

            void highlordDarionMograine_cast_unholyBlight(void)
            {
                me->CastSpell(me, SPELL_UNHOLY_BLIGHT);
                events.ScheduleEvent(SCRIPT_PHASE_IN_BATTLE_CAST_UNHOLY_BLIGHT, (TIMER_HIGHLORD_DARION_MOGRAINE_UNHOLY_BLIGHT_REPEAT * 1s));
            }

            void highlordDarionMograine_cast_antiMagicZone(void)
            {
                me->CastSpell(me, SPELL_ANTI_MAGIC_ZONE, CastSpellExtraArgs(true));
                events.ScheduleEvent(SCRIPT_PHASE_IN_BATTLE_CAST_ANTI_MAGIC_ZONE, (TIMER_HIGHLORD_DARION_MOGRAINE_ANTI_MAGIC_ZONE_REPEAT * 1s));
            }
            //combat ai functions end

            void summonRampagingAbominations(void)
            {
                for (unsigned int x = 0; x < NUMBER_RAMPAGING_ABOMINATION; x++)
                {
                    rampaging_abominations[x] = me->SummonCreature(ID_RAMPAGING_ABOMINATION, Spawn_Positions_Rampaging_Abomination_Battle[x], TEMPSUMMON_MANUAL_DESPAWN);
                    rampaging_abominations[x]->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_SILENCED | UNIT_FLAG_PACIFIED | UNIT_FLAG_NOT_SELECTABLE);
                    rampaging_abominations[x]->SetReactState(REACT_AGGRESSIVE);
                    rampaging_abominations[x]->GetMotionMaster()->MovePoint(0, scourgeMinion_respawn_battle, true);
                }

                rampaging_abominations_spawned = true;
            }

            void scourgeStartLosingBattle(void)
            {
                //holy lightning horizontal objects
                for (unsigned int x = 0; x < NUMBER_HOLY_LIGHTNING; x++)
                {
                    holy_lightnings_horizontal[x] = me->SummonGameObject(OBJECT_HOLY_LIGHTNING_HORIZONTAL, holy_lightning_spawn_locations[x], QuaternionData(), GO_SUMMON_TIMED_OR_CORPSE_DESPAWN);
                }

                //holy lightning vertical objects
                for (unsigned int x = 0; x < NUMBER_HOLY_LIGHTNING; x++)
                {
                    holy_lightnings_vertical[x] = me->SummonGameObject(OBJECT_HOLY_LIGHTNING_VERTICAL, holy_lightning_spawn_locations[x], QuaternionData(), GO_SUMMON_TIMED_OR_CORPSE_DESPAWN);
                }

                holy_lightning_spawned = true;
            }

            /*
            void killAllNonImportantScourgeUnits(void)
            {
                tirion->CastSpell(me, SPELL_LIGHT_OF_DAWN_KILL, CastSpellExtraArgs(true));

                //kill all flesh behemoths
                for (uint32 x = 0; x < NUMBER_FLESH_BEHEMOTH; x++)
                {
                    if (flesh_behemoths[x]->IsAlive())
                    {
                        flesh_behemoths[x]->KillSelf();
                    }
                }

                //kill all rampaging abominations
                for (unsigned int x = 0; x < NUMBER_RAMPAGING_ABOMINATION; x++)
                {
                    if (rampaging_abominations[x]->IsAlive())
                    {
                        rampaging_abominations[x]->KillSelf();
                    }
                }

                //kill all warriors of the frozen wastes
                for (uint32 x = 0; x < NUMBER_WARRIOR_OF_THE_FROZEN_WASTES; x++)
                {
                    if (warrior_of_the_frozen_wastes[x]->IsAlive())
                    {
                        warrior_of_the_frozen_wastes[x]->KillSelf();
                    }
                }

                //tell volatile ghoules to enter agressive react state and remove combat inhibiting flags
                for (uint32 x = 0; x < NUMBER_VOLATILE_GHOUL; x++)
                {
                    if (volatile_ghouls[x]->IsAlive())
                    {
                        volatile_ghouls[x]->KillSelf();
                    }
                }
            }*/

            void orbazFleeBattle(void)
            {
                orbaz->SetReactState(REACT_PASSIVE);
                orbaz->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_SILENCED | UNIT_FLAG_PACIFIED);
                orbaz->GetCombatManager().EndAllCombat();
                orbaz->CombatStop();
                orbaz->GetMotionMaster()->Clear();
                orbaz->GetMotionMaster()->MoveIdle();
                orbaz->Mount(25278);
                orbaz->AI()->Talk(ORBAZ_FLEES_FROM_BATTLE);
                orbaz->GetMotionMaster()->MovePoint(0, orbaz_bloodbane_fleeing_battle, true);
            }

            void killAllScourgeUnits(bool finalCall)
            {
                me->CastSpell(me, SPELL_LIGHT_OF_DAWN_KILL, CastSpellExtraArgs(true));

                if (finalCall)
                {
                    //rampaging abominations
                    for (unsigned int x = 0; x < NUMBER_RAMPAGING_ABOMINATION; x++)
                    {
                        if (rampaging_abominations[x]->IsAlive())
                        {
                            rampaging_abominations[x]->KillSelf();
                        }
                    }

                    //warriors of the frozen wastes
                    for (unsigned int x = 0; x < NUMBER_WARRIOR_OF_THE_FROZEN_WASTES; x++)
                    {
                        if (warrior_of_the_frozen_wastes[x]->IsAlive())
                        {
                            warrior_of_the_frozen_wastes[x]->KillSelf();;
                        }
                    }


                    //volatile ghouls
                    for (unsigned int x = 0; x < NUMBER_VOLATILE_GHOUL; x++)
                    {
                        if (volatile_ghouls[x]->IsAlive())
                        {
                            volatile_ghouls[x]->KillSelf();
                        }
                    }

                    //flesh behemoths
                    for (unsigned int x = 0; x < NUMBER_FLESH_BEHEMOTH; x++)
                    {
                        if (flesh_behemoths[x]->IsAlive())
                        {
                            flesh_behemoths[x]->KillSelf();
                        }
                    }

                    flesh_behemoths_spawned = false;
                    rampaging_abominations_spawned = false;
                    openening_scene_creatures_spawned = false;
                    corpses_despawned = true;
                }
            }

            void setupForBattleLost(void)
            {
                me->RemoveAllAuras();

                //despawn holy lightning horizontal objects
                for (unsigned int x = 0; x < NUMBER_HOLY_LIGHTNING; x++)
                {
                    if (holy_lightnings_horizontal[x])
                    {
                        holy_lightnings_horizontal[x]->DespawnOrUnsummon();
                        holy_lightnings_horizontal[x] = nullptr;
                    }
                }

                //despawn holy lightning vertical objects
                for (unsigned int x = 0; x < NUMBER_HOLY_LIGHTNING; x++)
                {
                    if (holy_lightnings_vertical[x])
                    {
                        holy_lightnings_vertical[x]->DespawnOrUnsummon();
                        holy_lightnings_vertical[x] = nullptr;
                    }
                }

                holy_lightning_spawned = false;

                //clean up darion ai
                me->SetReactState(REACT_PASSIVE);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_SILENCED | UNIT_FLAG_PACIFIED);
                me->GetCombatManager().EndAllCombat();
                me->GetMotionMaster()->Clear();
                me->GetMotionMaster()->MoveIdle();
                me->CombatStop();

                //clean up koltira ai
                koltira->SetReactState(REACT_PASSIVE);
                koltira->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_SILENCED | UNIT_FLAG_PACIFIED);
                koltira->GetCombatManager().EndAllCombat();
                koltira->GetMotionMaster()->Clear();
                koltira->GetMotionMaster()->MoveIdle();
                koltira->CombatStop();

                //clean up thassarian ai
                thassarian->SetReactState(REACT_PASSIVE);
                thassarian->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_SILENCED | UNIT_FLAG_PACIFIED);
                thassarian->GetCombatManager().EndAllCombat();
                thassarian->GetMotionMaster()->Clear();
                thassarian->GetMotionMaster()->MoveIdle();
                thassarian->CombatStop();

                //clean up all defenders of the light ai
                for (uint32 x = 0; x < NUMBER_DEFENDER_OF_THE_LIGHT; x++)
                {
                    defenders_of_the_light[x]->SetReactState(REACT_PASSIVE);
                    defenders_of_the_light[x]->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_SILENCED | UNIT_FLAG_PACIFIED);
                    defenders_of_the_light[x]->GetCombatManager().EndAllCombat();
                    defenders_of_the_light[x]->GetMotionMaster()->Clear();
                    defenders_of_the_light[x]->GetMotionMaster()->MoveIdle();
                    defenders_of_the_light[x]->CombatStop();
                }

                //clean up maxwell ai
                maxwell->SetReactState(REACT_PASSIVE);
                maxwell->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_SILENCED | UNIT_FLAG_PACIFIED);
                maxwell->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                maxwell->RemoveAurasDueToSpell(SPELL_FEIGN_DEATH);
                maxwell->GetCombatManager().EndAllCombat();
                maxwell->GetMotionMaster()->Clear();
                maxwell->GetMotionMaster()->MoveIdle();
                maxwell->CombatStop();

                //clean up korfax ai
                korfax->SetReactState(REACT_PASSIVE);
                korfax->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_SILENCED | UNIT_FLAG_PACIFIED);
                korfax->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                korfax->RemoveAurasDueToSpell(SPELL_FEIGN_DEATH);
                korfax->GetCombatManager().EndAllCombat();
                korfax->GetMotionMaster()->Clear();
                korfax->GetMotionMaster()->MoveIdle();
                korfax->CombatStop();

                //clean up leonid ai
                leonid->SetReactState(REACT_PASSIVE);
                leonid->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_SILENCED | UNIT_FLAG_PACIFIED);
                leonid->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                leonid->RemoveAurasDueToSpell(SPELL_FEIGN_DEATH);
                leonid->GetCombatManager().EndAllCombat();
                leonid->GetMotionMaster()->Clear();
                leonid->GetMotionMaster()->MoveIdle();
                leonid->CombatStop();

                //clean up nicholas ai
                nicholas->SetReactState(REACT_PASSIVE);
                nicholas->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_SILENCED | UNIT_FLAG_PACIFIED);
                nicholas->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                nicholas->RemoveAurasDueToSpell(SPELL_FEIGN_DEATH);
                nicholas->GetCombatManager().EndAllCombat();
                nicholas->GetMotionMaster()->Clear();
                nicholas->GetMotionMaster()->MoveIdle();
                nicholas->CombatStop();

                //clean up eligor ai
                eligor->SetReactState(REACT_PASSIVE);
                eligor->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_SILENCED | UNIT_FLAG_PACIFIED);
                eligor->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                eligor->RemoveAurasDueToSpell(SPELL_FEIGN_DEATH);
                eligor->GetCombatManager().EndAllCombat();
                eligor->GetMotionMaster()->Clear();
                eligor->GetMotionMaster()->MoveIdle();
                eligor->CombatStop();

                //clean up rayne ai
                rayne->SetReactState(REACT_PASSIVE);
                rayne->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_SILENCED | UNIT_FLAG_PACIFIED);
                rayne->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                rayne->RemoveAurasDueToSpell(SPELL_FEIGN_DEATH);
                rayne->GetCombatManager().EndAllCombat();
                rayne->GetMotionMaster()->Clear();
                rayne->GetMotionMaster()->MoveIdle();
                rayne->GetMotionMaster()->MoveIdle();
                rayne->CombatStop();

                //clean up rimblat ai
                rimblat->SetReactState(REACT_PASSIVE);
                rimblat->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_SILENCED | UNIT_FLAG_PACIFIED);
                rimblat->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                rimblat->RemoveAurasDueToSpell(SPELL_FEIGN_DEATH);
                rimblat->GetCombatManager().EndAllCombat();
                rimblat->GetMotionMaster()->Clear();
                rimblat->GetMotionMaster()->MoveIdle();
                rimblat->CombatStop();
            }

            void battleLostEveryoneMoveToPostions(void)
            {
                //defenders of the light move into positions
                for (uint32 x = 0; x < NUMBER_DEFENDER_OF_THE_LIGHT; x++)
                {
                    defenders_of_the_light[x]->GetMotionMaster()->MovePoint((x + 1), defender_of_the_light_to_lights_hope_battle_lost[x], true);
                }

                //maxwell move into position
                maxwell->GetMotionMaster()->MovePoint(1, maxwell_to_lights_hope_battle_lost, true);

                //korfax move into position
                korfax->GetMotionMaster()->MovePoint(1, korfax_to_lights_hope_battle_lost, true);

                //leonid move into position
                leonid->GetMotionMaster()->MovePoint(1, leonid_to_lights_hope_battle_lost, true);

                //nicholas move into position
                nicholas->GetMotionMaster()->MovePoint(1, nicholas_to_lights_hope_battle_lost, true);

                //eligor move into position
                eligor->GetMotionMaster()->MovePoint(1, eligor_to_lights_hope_battle_lost, true);

                //rayne move into position
                rayne->GetMotionMaster()->MovePoint(1, rayne_to_lights_hope_battle_lost, true);

                //rimblat move into position
                rimblat->GetMotionMaster()->MovePoint(1, rimblat_to_lights_hope_battle_lost, true);

                //koltira begin movement
                koltira->SetWalk(true);
                koltira->SetCanFly(true);
                koltira->SetDisableGravity(true);
                koltira->AddUnitMovementFlag(MOVEMENTFLAG_FLYING);
                koltira->CastSpell(koltira, SPELL_LIGHT_OF_DAWN_PRISON);
                //koltira->GetMotionMaster()->MovePoint(1, koltira->GetPositionX(), koltira->GetPositionY(), (koltira->GetPositionZ() + 10.0f), false);
                koltira->GetMotionMaster()->MovePoint(2, koltira_to_lights_hope_battle_lost, true);

                //thassarian begin movement
                thassarian->SetWalk(true);
                thassarian->SetCanFly(true);
                thassarian->SetDisableGravity(true);
                thassarian->AddUnitMovementFlag(MOVEMENTFLAG_FLYING);
                thassarian->CastSpell(thassarian, SPELL_LIGHT_OF_DAWN_PRISON);
                //thassarian->GetMotionMaster()->MovePoint(1, thassarian->GetPositionX(), thassarian->GetPositionY(), (thassarian->GetPositionZ() + 10.0f), false);
                thassarian->GetMotionMaster()->MovePoint(2, thassarian_to_lights_hope_battle_lost, true);

                //darion begin movement
                me->SetWalk(true);
                me->SetCanFly(true);
                me->SetDisableGravity(true);
                me->AddUnitMovementFlag(MOVEMENTFLAG_FLYING);
                me->CastSpell(me, SPELL_LIGHT_OF_DAWN_PRISON);
                //me->GetMotionMaster()->MovePoint(1, me->GetPositionX(), me->GetPositionY(), (me->GetPositionZ() + 10.0f), false);
                me->GetMotionMaster()->MovePoint(2, darion_to_lights_hope_battle_lost, true);
            }

            //this is called whenever a summon creature dies.
            //summonList is the master list of the type of npc that died
            //summonSpawnLocations is the list of the spawn locations that should be refferenced when respawning the creature
            //size is the respective size of summonList and summonSpawnLocations
            //summon is the creature that dies passed by SummonedCreatureDies()
            void handleSummonedCreatureDeath(TempSummon *summonList[], Position const summonSpawnLocations[], uint32 size, Creature* summon)
            {
                //determine the index in the array the creature is in
                int creature_index = -1;

                //iterate through summonList
                for (uint32 x = 0; x < size; x++)
                {
                    //try to locate what index the creature is at within the list by looking for a matching guid
                    if (summonList[x]->GetGUID() == summon->GetGUID())
                    {
                        //if found, assign
                        creature_index = x;
                    }
                }

                //if a match wasn't found, THIS WOULD BE BAD
                if (creature_index == -1)
                {
                    //me->Say("error", LANG_UNIVERSAL);
                }
                else
                {
                    //overwrite the dead creature in the list with a new one by spawning one and assigning it to that index
                    uint32 deadSummonEntry = summon->GetEntry();
                    switch (deadSummonEntry)
                    {
                    case ID_WARRIOR_OF_THE_FROZEN_WASTES:
                        summonList[creature_index] = summon_Warrior_or_ghoul(true, summonSpawnLocations[creature_index]);
                        if (current_phase == PHASE_CHARGE_INTO_BATTLE || current_phase == PHASE_IN_BATTLE)
                        {
                            remaining_scourge -= 1;
                            updateWorldStateForPlayers(WORLD_STATE_SCOURGE_COUNT, remaining_scourge);
                        }
                        break;
                    case ID_VOLATILE_GHOUL:
                        summonList[creature_index] = summon_Warrior_or_ghoul(false, summonSpawnLocations[creature_index]);
                        if (current_phase == PHASE_CHARGE_INTO_BATTLE || current_phase == PHASE_IN_BATTLE)
                        {
                            remaining_scourge -= 1;
                            updateWorldStateForPlayers(WORLD_STATE_SCOURGE_COUNT, remaining_scourge);
                        }
                        break;
                    case ID_FLESH_BEHEMOTH:
                    case ID_RAMPAGING_ABOMINATION:
                        summonList[creature_index] = me->SummonCreature(deadSummonEntry, summonSpawnLocations[creature_index], TEMPSUMMON_MANUAL_DESPAWN);
                        if (current_phase == PHASE_CHARGE_INTO_BATTLE || current_phase == PHASE_IN_BATTLE)
                        {
                            summonList[creature_index]->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_SILENCED | UNIT_FLAG_PACIFIED);
                            summonList[creature_index]->SetReactState(REACT_AGGRESSIVE);
                            if (summonList[creature_index]->IsAlive())
                            {
                                summonList[creature_index]->GetMotionMaster()->MovePoint(0, scourgeMinion_respawn_battle, true);
                            }
                            remaining_scourge -= 1;
                            updateWorldStateForPlayers(WORLD_STATE_SCOURGE_COUNT, remaining_scourge);
                        }
                        break;
                    case ID_DEFENDER_OF_THE_LIGHT:
                        summonList[creature_index] = me->SummonCreature(deadSummonEntry, summonSpawnLocations[creature_index], TEMPSUMMON_MANUAL_DESPAWN);
                        if (current_phase == PHASE_CHARGE_INTO_BATTLE || current_phase == PHASE_IN_BATTLE)
                        {
                            summonList[creature_index]->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_SILENCED | UNIT_FLAG_PACIFIED);
                            summonList[creature_index]->SetReactState(REACT_AGGRESSIVE);
                            summonList[creature_index]->GetMotionMaster()->MovePoint(0, scourgeMinion_respawn_battle, true);
                            remaining_argent_dawn -= 1;
                            updateWorldStateForPlayers(WORLD_STATE_DEFENDERS_COUNT, remaining_argent_dawn);
                        }
                        break;
                    default:
                        break;
                    }
                    
                    //add the dead summon to the list of corpses that need to be despawned
                    corpse_cleanup_list.push_back(summon);
                    //schedule an event to handle the despawning of the corpse
                    events.ScheduleEvent(SCRIPT_PHASE_ANY_DESPAWN_SUMMON_CORPSE, 10s);
                }
            }

            //overloaded function to work with just a single spawn location instead of an array
            void handleSummonedCreatureDeath(TempSummon *summonList[], Position const summonSpawnLocation, uint32 size, Creature* summon)
            {
                //determine the index in the array the creature is in
                int creature_index = -1;

                //iterate through summonList
                for (uint32 x = 0; x < size; x++)
                {
                    //try to locate what index the creature is at within the list by looking for a matching guid
                    if (summonList[x]->GetGUID() == summon->GetGUID())
                    {
                        //if found, assign
                        creature_index = x;
                    }
                }

                //if a match wasn't found, THIS WOULD BE BAD
                if (creature_index == -1)
                {
                    //me->Say("error", LANG_UNIVERSAL);
                }
                else
                {
                    //overwrite the dead creature in the list with a new one by spawning one and assigning it to that index
                    uint32 deadSummonEntry = summon->GetEntry();
                    switch (deadSummonEntry)
                    {
                    case ID_WARRIOR_OF_THE_FROZEN_WASTES:
                        summonList[creature_index] = summon_Warrior_or_ghoul(true, summonSpawnLocation);
                        if (current_phase == PHASE_CHARGE_INTO_BATTLE || current_phase == PHASE_IN_BATTLE)
                        {
                            remaining_scourge -= 1;
                            updateWorldStateForPlayers(WORLD_STATE_SCOURGE_COUNT, remaining_scourge);
                        }
                        break;
                    case ID_VOLATILE_GHOUL:
                        summonList[creature_index] = summon_Warrior_or_ghoul(false, summonSpawnLocation);
                        if (current_phase == PHASE_CHARGE_INTO_BATTLE || current_phase == PHASE_IN_BATTLE)
                        {
                            remaining_scourge -= 1;
                            updateWorldStateForPlayers(WORLD_STATE_SCOURGE_COUNT, remaining_scourge);
                        }
                        break;
                    case ID_FLESH_BEHEMOTH:
                    case ID_RAMPAGING_ABOMINATION:
                        summonList[creature_index] = me->SummonCreature(deadSummonEntry, summonSpawnLocation, TEMPSUMMON_MANUAL_DESPAWN);
                        if (current_phase == PHASE_CHARGE_INTO_BATTLE || current_phase == PHASE_IN_BATTLE)
                        {
                            summonList[creature_index]->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_SILENCED | UNIT_FLAG_PACIFIED);
                            summonList[creature_index]->SetReactState(REACT_AGGRESSIVE);
                            if (summonList[creature_index]->IsAlive())
                            {
                                summonList[creature_index]->GetMotionMaster()->MovePoint(0, scourgeMinion_respawn_battle, true);
                            }
                            remaining_scourge -= 1;
                            updateWorldStateForPlayers(WORLD_STATE_SCOURGE_COUNT, remaining_scourge);
                        }
                        break;
                    case ID_DEFENDER_OF_THE_LIGHT:
                        summonList[creature_index] = me->SummonCreature(deadSummonEntry, summonSpawnLocation, TEMPSUMMON_MANUAL_DESPAWN);
                        if (current_phase == PHASE_CHARGE_INTO_BATTLE || current_phase == PHASE_IN_BATTLE)
                        {
                            summonList[creature_index]->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_SILENCED | UNIT_FLAG_PACIFIED);
                            summonList[creature_index]->SetReactState(REACT_AGGRESSIVE);
                            summonList[creature_index]->GetMotionMaster()->MovePoint(0, scourgeMinion_respawn_battle, true);
                            remaining_argent_dawn -= 1;
                            updateWorldStateForPlayers(WORLD_STATE_DEFENDERS_COUNT, remaining_argent_dawn);
                        }
                        break;
                        break;
                    default:
                        break;
                    }

                    //add the dead summon to the list of corpses that need to be despawned
                    corpse_cleanup_list.push_back(summon);
                    //schedule an event to handle the despawning of the corpse
                    events.ScheduleEvent(SCRIPT_PHASE_ANY_DESPAWN_SUMMON_CORPSE, 10s);
                }
            }

            //overloaded function to work with just a single spawn location instead of an array and just a single spawn instead of an array of spawns
            //a pointer reference is used for summonPointer because, say koltira were the one who died in a hypothetical case,
            //what would happen is summonPointer would be recieved as a copy of the koltira pointer instead of the original.
            //so, for summonPointer = me->SummonCreature(deadSummonEntry, summonSpawnLocation, TEMPSUMMON_MANUAL_DESPAWN), the original koltira pointer
            //would not be updated and therefor cause a crash later down the road if anything tried to access that pointer
            void handleSummonedCreatureDeath(TempSummon *&summonPointer, Position const summonSpawnLocation, Creature* summon)
            {
                    //overwrite the dead creature in the list with a new one by spawning one and assigning it to that index
                    uint32 deadSummonEntry = summon->GetEntry();
                    switch (deadSummonEntry)
                    {
                    case ID_KOLTIRA_DEATHWEAVER:
                    case ID_ORBAZ_BLOODBANE:
                    case ID_THASSARIAN:
                    case ID_LORD_MAXWELL_TYROSUS:
                    case ID_KORFAX_CHAMPION_OF_THE_LIGHT:
                    case ID_LEONID_BARTHALOMEW_THE_REVERED:
                    case ID_DUKE_NICHOLAS_ZVERENHOFF:
                    case ID_COMMANDER_ELIGOR_DAWNBRINGER:
                    case ID_RAYNE:
                    case ID_RIMBLAT_EARTHSHATTER:
                        summonPointer = me->SummonCreature(deadSummonEntry, summonSpawnLocation, TEMPSUMMON_MANUAL_DESPAWN);
                        break;
                    default:
                        break;
                    }

                    //add the dead summon to the list of corpses that need to be despawned
                    corpse_cleanup_list.push_back(summon);

                    //schedule an event to handle the despawning of the corpse
                    events.ScheduleEvent(SCRIPT_PHASE_ANY_DESPAWN_SUMMON_CORPSE, 10s);
            }

            void handleSummonedCreatureDeath(Creature* summon)
            {
                //add the dead summon to the list of corpses that need to be despawned
                corpse_cleanup_list.push_back(summon);

                //schedule an event to handle the despawning of the corpse
                events.ScheduleEvent(SCRIPT_PHASE_ANY_DESPAWN_SUMMON_CORPSE, 10s);
            }

            //changes the zone's weather state to raining if true, no weather if false
            void setZoneWeatherToRaining(bool raining)
            {
                if (raining)
                {
                    //wtf is weather grade?? TRINITY COMMENT YOUR SHIT PLEASE
                    me->GetMap()->SetZoneWeather(me->GetZoneId(), 4, 6.0f);
                    //me->Say("weather set to raining", LANG_UNIVERSAL);
                }
                else
                {
                    me->GetMap()->SetZoneWeather(me->GetZoneId(), 0, 0.0f);
                    //me->Say("weather set to none", LANG_UNIVERSAL);
                }
            }

            //handles phase transitions and anything that needs to occur immediately when transitioning
            void progressEvent(void)
            {
                switch (current_phase)
                {
                case PHASE_WAITING_FOR_PLAYERS:
                    current_phase = PHASE_WAITING_FOR_BATTLE;
                    //me->Say("Entered phase: PHASE_WAITING_FOR_BATTLE", LANG_UNIVERSAL);
                    updateWorldStateForPlayers(WORLD_STATE_COUNTDOWN_ENABLE, 1);
                    updateWorldStateForPlayers(WORLD_STATE_COUNTDOWN_TIME, event_countdown_remaining_time);
                    events.ScheduleEvent(SCRIPT_PHASE_WAITING_FOR_BATTLE_UPDATE_EVENT_COUNTDOWN_WORLDSTATE, 60s);
                    events.ScheduleEvent(SCRIPT_PHASE_WAITING_FOR_BATTLE_TALK_1, 2s);
                    events.ScheduleEvent(SCRIPT_PHASE_WAITING_FOR_BATTLE_TALK_2, ((ECOUNTER_COUNTDOWN_TIME_MINUTES * 60s) - (ECOUNTER_COUNTDOWN_TIME_MINUTES * 30s)));
                    events.ScheduleEvent(SCRIPT_PHASE_WAITING_FOR_BATTLE_TALK_3, ((ECOUNTER_COUNTDOWN_TIME_MINUTES * 60s) - 5s));
                    events.ScheduleEvent(SCRIPT_PHASE_WAITING_FOR_BATTLE_TO_PHASE_OPENING_SCENE, (ECOUNTER_COUNTDOWN_TIME_MINUTES * 60s));
                    break;
                case PHASE_WAITING_FOR_BATTLE:
                    me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER);
                    current_phase = PHASE_OPENING_SCENE;
                    //me->Say("Entered phase: PHASE_OPENING_SCENE", LANG_UNIVERSAL);
                    events.ScheduleEvent(SCRIPT_PHASE_OPENING_SCENE_TALK_1, 5s);
                    events.ScheduleEvent(SCRIPT_PHASE_OPENING_SCENE_TALK_2, 14s);
                    events.ScheduleEvent(SCRIPT_PHASE_OPENING_SCENE_SUMMON, 15s);
                    events.ScheduleEvent(SCRIPT_PHASE_ANY_SET_WEATHER_TO_RAINING_REPEATING, 15s);
                    events.ScheduleEvent(SCRIPT_PHASE_OPENING_SCENE_TALK_3, 20s);
                    events.ScheduleEvent(SCRIPT_PHASE_OPENING_SCENE_SCOURGE_ROAR, 31s);
                    events.ScheduleEvent(SCRIPT_PHASE_OPENING_SCENE_TO_PHASE_CHARGE_INTO_BATTLE, 32s);
                    break;
                case PHASE_OPENING_SCENE:
                    current_phase = PHASE_CHARGE_INTO_BATTLE;
                    //me->Say("Entered phase: PHASE_CHARGE_INTO_BATTLE", LANG_UNIVERSAL);
                    summonAllLightsHopeNPCs();
                    allScourgeUnitsMoveToLightsHope_charge_into_battle();
                    events.ScheduleEvent(SCRIPT_PHASE_CHARGING_INTO_BATTLE_TO_IN_BATTLE, 15s);
                    break;
                case PHASE_CHARGE_INTO_BATTLE:
                    current_phase = PHASE_IN_BATTLE;
                    //me->Say("Entered phase: PHASE_IN_BATTLE", LANG_UNIVERSAL);
                    maxwell->AI()->Talk(MAXWELL_IN_BATTLE);
                    me->CastSpell(me, SPELL_THE_MIGHT_OF_MOGRAINE, CastSpellExtraArgs(true));
                    allUnitsPrepareForCombat();
                    events.ScheduleEvent(SCRIPT_PHASE_IN_BATTLE_SUMMON_RAMPAGING_ABOMINATIONS, 20s);
                    break;
                case PHASE_IN_BATTLE:
                    current_phase = PHASE_BATTLE_LOST;
                    //me->Say("Entered phase: PHASE_BATTLE_LOST", LANG_UNIVERSAL);
                    events.ScheduleEvent(SCRIPT_PHASE_BATTLE_LOST_SETUP_NPCS, 6s);
                    events.ScheduleEvent(SCRIPT_PHASE_BATTLE_LOST_TIRION_TALK_1, 4s);
                    events.ScheduleEvent(SCRIPT_PHASE_BATTLE_LOST_EVERYONE_MOVE_TO_POSITIONS, 8s);
                    break;
                case PHASE_BATTLE_LOST:
                    current_phase = PHASE_FLASH_BACK;
                    //me->Say("Entered phase: PHASE_FLASH_BACK", LANG_UNIVERSAL);
                    alexandros = me->SummonCreature(ID_HIGHLORD_ALEXANDROS_MOGRAINE, Spawn_Positions_Highlord_Alexandros_Mograine, TEMPSUMMON_MANUAL_DESPAWN);
                    alexandros->CastSpell(alexandros, SPELL_ALEXANDROS_SPAWN);

                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_ALEXANDROS_TALK_1, 5s);
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_DARION_TURN_TO_FACE_ALEXANDROS, 7s);
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_DARION_TALK_1, 8s);
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_SPAWN_YOUNG_DARION, 10s);
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_DARION_TALK_2, 11s);
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_YOUNG_DARION_TALK_1, 13s);
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_YOUNG_DARION_RUN_TO_ALEXANDROS, 15s);
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_YOUNG_DARION_TALK_2, 17s);
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_YOUNG_DARION_TALK_3, 21s);
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_ALEXANDROS_TALK_2, 25s);
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_YOUNG_DARION_TALK_4, 32s);
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_ALEXANDROS_TALK_3, 39s);
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_TIRION_WALK_NEAR_DARION, 40s);
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_YOUNG_DARION_TALK_5, 53s);
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_ALEXANDROS_TALK_4, 64s);
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_ALEXANDROS_TALK_5, 92s);
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_LICH_KING_SPAWN, 96s);
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_LICH_KING_TALK_1, 100s);
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_LICH_KING_TALK_2, 104s);
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_ALEXANDROS_DESPAWN, 106s);
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_DARION_STAND_UP, 108s);
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_DARION_TALK_3, 110s);
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_LICH_KING_WALK_FORWARD, 113s);
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_DARION_CHARGE_AT_LICH_KING, 119s);
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_DARION_KNOCKED_BACK, (119s + 500ms));
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_DARION_KNEEL_AFTER_KNOCKBACK, (121s + 500ms));
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_TIRION_TALK_1, 126s);
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_LICH_KING_LAUGH, 131s);
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_LICH_KING_TALK_3, 135s);
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_LICH_KING_POINT_AT_TIRION, 144s);
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_LICH_KING_TALK_4, 150s);
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_LICH_KING_DRAIN_TIRION, 167s);
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_ALL_DAWN_ATTACK_LICH_KING, 169s);
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_LICH_CAST_APOCOLYPSE_ON_ALL_DAWN, 172s);
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_ALL_DAWN_KNOCKED_DOWN, 175s);
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_DARION_TALK_4, 180s);
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_DARION_TALK_5, 184s);
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_DARION_THROW_ASHBRINGER_AT_TIRION, 186s);
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_DARION_COLLAPSE, 190s);
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_TIRION_PURIFIES_ASHBRINGER, 190s);
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_TIRION_EQUIPS_ASHBRINGER, 191s);
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_TIRION_TALK_2, 193s);
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_LICH_KING_TALK_5, 197s);
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_TIRION_TALK_3, 201s);
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_TIRION_CHARGE_AT_LICH_KING, 203s);
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_TIRION_LAND_FROM_CHARGE, (203s + 500ms));
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_LICH_KING_TALK_6, 205s);
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_LICH_KING_TALK_7, 211s);
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_LICH_KING_TALK_8, 219s);
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_LICH_KING_CAST_DESPAWN_SPELL, 229s);
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_LICH_KING_DESPAWN, 230s);
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_TIRION_WALK_TO_DARION, 232s);
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_TIRION_CAST_LAY_ON_HANDS_ON_DARION, 237s);
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_TIRION_TALK_4, 241s);
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_TIRION_WALK_AWAY_FROM_DARION, 244s);
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_TIRION_TALK_5, 252s);
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_TIRION_TALK_6, 267s);
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_TIRION_TALK_7, 273s);
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_TIRION_TALK_8, 284s);
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_TIRION_TALK_9, 295s);
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_TIRION_TALK_10, 304s);
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_TIRION_TALK_11, 312s);
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_DARION_GET_UP, 316s);
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_DARION_TALK_6, 318s);
                    events.ScheduleEvent(SCRIPT_PHASE_FLASH_BACK_TO_PHASE_EVENT_DONE, 330s);

                    break;
                case PHASE_FLASH_BACK:
                    current_phase = PHASE_EVENT_DONE;

                    //give quest credit
                    if (!playerList.empty())
                    {
                        for (std::list<Player*>::iterator itr = playerList.begin(); itr != playerList.end(); ++itr)
                        {
                            Player *player = *itr;

                            if (player->IsInWorld())
                            {
                                player->CastSpell(player, SPELL_QUEST_COMPLETE, true);
                                player->SetQuestStatus(12801, QUEST_STATUS_COMPLETE, true);
                            }
                        }
                    }

                    me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER);
                    events.ScheduleEvent(SCRIPT_PHASE_ANY_RESPAWN, (EVENT_TIMER_RESET_COOLDOWN * 60s));
                    break;
                default:
                    break;
                }
            }

            //called when the creature is first instantiated either by first spawn or respawn
            npc_highlord_darion_mograineAI(Creature* creature) : ScriptedAI(creature)
            {
                //instantiate variables
                koltira_spawned = false;
                orbaz_spawned = false;
                thassarian_spawned = false;
                flesh_behemoths_spawned = false;
                openening_scene_creatures_spawned = false;
                rampaging_abominations_spawned = false;
                lights_hope_creatures_spawned = false;
                young_mograine_spawned = false;
                alexandros_spawned = false;
                lich_king_spawned = false;
                tirion_spawned = false;
                holy_lightning_spawned = false;
                light_of_dawn_spawned = false;
                worldstates_reset = false;
                corpses_despawned = false;
                remaining_scourge = ENCOUNTER_TOTAL_SCOURGE;
                remaining_argent_dawn = ENCOUNTER_TOTAL_DAWN;
                event_countdown_remaining_time = ECOUNTER_COUNTDOWN_TIME_MINUTES;
                events = EventMap();
                playerList = std::list<Player*>();
                scriptedSummonList_for_attack_animation = std::list<TempSummon*>();
                scriptedSummonList_for_spawn_cleanup = std::list<TempSummon*>();
                corpse_cleanup_list = std::list<Creature*>();
                spawn_initialize();

                //instantiate combat AI variables
                me->SetReactState(REACT_PASSIVE);
                entry = me->GetEntry();
                targetAquisitionRange = COMBAT_TARGET_AQUISITION_RANGE;
                targetList = std::list<Unit*>();
                tempTarget1 = nullptr;
                first_outOfCombat_recent = true;
                first_inCombat_recent = true;
                first_inCombat_ever = true;
                casting = false;
            }

            //called when the creature's AI is destroyed either by the creature despawning or script hotswapping
            ~npc_highlord_darion_mograineAI(void) override
            {
                /*this is only here in case the creature's AI is forcefully destroyed but the creature is not, such as in the event of script hotswapping occurring.
                Through the failsafe in despawnSummons() design, this call will only despawn summons under this explicit case. Since LeavingWorld() would be called upon
                in any normal case of the creature's AI being destroyed through despawn, that would cover the despawn of the creatures safely and then this call will do nothing.
                There are some issues with calling specific things in the creature's deconstructor such as despawning, as all despawning has a technical source that is called through hooks.
                If a creature that doesn't exist is called through a hook, the server will crash which is ***BAD***. Hence, this needs to exist only as a failsafe*/
                events.Reset();
                despawnSummons();
                resetWorldStates();
            }

            void MovementInform(uint32 type, uint32 id) override
            {
                if (id == 1)
                {
                    me->GetMotionMaster()->Clear();
                    me->GetMotionMaster()->MoveIdle();
                    me->GetMotionMaster()->MovePoint(2, darion_to_lights_hope_battle_lost.GetPositionX(), darion_to_lights_hope_battle_lost.GetPositionY(), (darion_to_lights_hope_battle_lost.GetPositionZ() + 10.0f));
                }
                else if (id == 2)
                {
                    me->GetMotionMaster()->Clear();
                    me->GetMotionMaster()->MoveIdle();
                    me->SetWalk(false);
                    me->SetCanFly(false);
                    me->SetDisableGravity(false);
                    me->RemoveUnitMovementFlag(MOVEMENTFLAG_FLYING);
                    me->RemoveAurasDueToSpell(SPELL_LIGHT_OF_DAWN_PRISON);
                    me->GetMotionMaster()->MoveFall();
                    me->SetFacingTo(darion_to_lights_hope_battle_lost.GetOrientation(), true);

                    events.ScheduleEvent(SCRIPT_PHASE_BATTLE_LOST_DARION_TALK_1, 2s);
                    events.ScheduleEvent(SCRIPT_PHASE_BATTLE_LOST_DKS_STAND_DOWN, 7s);
                    events.ScheduleEvent(SCRIPT_PHASE_BATTLE_LOST_DARION_KNEEL, 10s);
                    events.ScheduleEvent(SCRIPT_PHASE_BATTLE_LOST_DKS_KNEEL, 12s);
                    events.ScheduleEvent(SCRIPT_PHASE_BATTLE_LOST_TIRON_TALK_2, 16s);

                    events.ScheduleEvent(SCRIPT_PHASE_BATTLE_LOST_TIRON_TALK_3, 34s);
                    events.ScheduleEvent(SCRIPT_PHASE_BATTLE_LOST_TIRON_TALK_4, 46s);
                    events.ScheduleEvent(SCRIPT_PHASE_BATTLE_LOST_DIRION_TALK_2, 60s);
                    events.ScheduleEvent(SCRIPT_PHASE_BATTLE_LOST_DIRION_POINT_AT_TIRION, 61s);
                    events.ScheduleEvent(SCRIPT_PHASE_BATTLE_LOST_TO_PHASE_FLASH_BACK, 67s);
                }
            }

            //used to handle npcs that have an invincibility hp value
            void DamageTaken(Unit* attacker, uint32& damage) override
            {
                if ((me->GetHealth() - damage) <= INVINCIBILITY_HP)
                {
                    damage = me->GetHealth() - INVINCIBILITY_HP;
                }

                if (damage >= me->GetHealth() - INVINCIBILITY_HP)
                {
                    damage = 0;
                    me->SetHealth(INVINCIBILITY_HP);
                }
            }

            // Called when the unit is about to be removed from the world (despawn, grid unload, corpse disappearing, player logging out etc.)
            void LeavingWorld() override
            {
                events.Reset();
                setZoneWeatherToRaining(false);
                despawnSummons();
                resetWorldStates();
            }

            //on reset either by exiting combat or script hotswapping
            void Reset() override
            {
                //me->Say("reset", LANG_UNIVERSAL);
            }

            void JustDied(Unit* killer) override
            {
                //me->Say("respawning", LANG_UNIVERSAL);
                me->DespawnOrUnsummon();
            }

            //called each time that a summoned unit dies
            void SummonedCreatureDies(Creature* summon, Unit* killer) override
            {
                //std::string test = summon->GetName() + " just died.";
                //me->Say(test, LANG_UNIVERSAL);

                uint32 summon_creature_id = summon->GetEntry();

                switch (current_phase)
                {
                case PHASE_WAITING_FOR_PLAYERS:
                case PHASE_WAITING_FOR_BATTLE:
                    switch (summon_creature_id)
                    {
                    case ID_FLESH_BEHEMOTH:
                        handleSummonedCreatureDeath(flesh_behemoths, Spawn_Positions_Flesh_Behemoth, NUMBER_FLESH_BEHEMOTH, summon);
                        break;
                    case ID_KOLTIRA_DEATHWEAVER:
                        handleSummonedCreatureDeath(koltira, Spawn_Positions_Koltira_Deathweaver, summon);
                        break;
                    case ID_ORBAZ_BLOODBANE:
                        handleSummonedCreatureDeath(orbaz, Spawn_Positions_Orbaz_Bloodbane, summon);
                        break;
                    case ID_THASSARIAN:
                        handleSummonedCreatureDeath(thassarian, Spawn_Positions_Thassarian, summon);
                        break;
                    }
                    break;
                case PHASE_OPENING_SCENE:
                    switch (summon_creature_id)
                    {
                    case ID_FLESH_BEHEMOTH:
                        handleSummonedCreatureDeath(flesh_behemoths, Spawn_Positions_Flesh_Behemoth, NUMBER_FLESH_BEHEMOTH, summon);
                        break;
                    case ID_WARRIOR_OF_THE_FROZEN_WASTES:
                        handleSummonedCreatureDeath(warrior_of_the_frozen_wastes, Spawn_Positions_Warrior_Of_The_Frozen_Wastes, NUMBER_WARRIOR_OF_THE_FROZEN_WASTES, summon);
                        break;
                    case ID_VOLATILE_GHOUL:
                        handleSummonedCreatureDeath(volatile_ghouls, Spawn_Positions_Volatile_Ghoul, NUMBER_VOLATILE_GHOUL, summon);
                        break;
                    case ID_KOLTIRA_DEATHWEAVER:
                        handleSummonedCreatureDeath(koltira, Spawn_Positions_Koltira_Deathweaver, summon);
                        break;
                    case ID_ORBAZ_BLOODBANE:
                        handleSummonedCreatureDeath(orbaz, Spawn_Positions_Orbaz_Bloodbane, summon);
                        break;
                    case ID_THASSARIAN:
                        handleSummonedCreatureDeath(thassarian, Spawn_Positions_Thassarian, summon);
                        break;
                    default:
                        break;
                    }
                    break;
                case PHASE_CHARGE_INTO_BATTLE:
                case PHASE_IN_BATTLE:
                    switch (summon_creature_id)
                    {
                    case ID_FLESH_BEHEMOTH:
                        handleSummonedCreatureDeath(flesh_behemoths, Spawn_Positions_Flesh_Behemoth_Battle, NUMBER_FLESH_BEHEMOTH, summon);
                        break;
                    case ID_RAMPAGING_ABOMINATION:
                        handleSummonedCreatureDeath(rampaging_abominations, Spawn_Positions_Rampaging_Abomination_Battle, NUMBER_RAMPAGING_ABOMINATION, summon);
                        break;
                    case ID_WARRIOR_OF_THE_FROZEN_WASTES:
                        handleSummonedCreatureDeath(warrior_of_the_frozen_wastes, Spawn_Positions_Warrior_Of_The_Frozen_Wastes_Battle, NUMBER_WARRIOR_OF_THE_FROZEN_WASTES, summon);
                        break;
                    case ID_VOLATILE_GHOUL:
                        handleSummonedCreatureDeath(volatile_ghouls, Spawn_Positions_Volatile_Ghoul_Battle, NUMBER_VOLATILE_GHOUL, summon);
                        break;
                    case ID_KOLTIRA_DEATHWEAVER:
                        handleSummonedCreatureDeath(koltira, me->GetPosition(), summon);
                        break;
                    case ID_ORBAZ_BLOODBANE:
                        handleSummonedCreatureDeath(orbaz, me->GetPosition(), summon);
                        break;
                    case ID_THASSARIAN:
                        handleSummonedCreatureDeath(thassarian, me->GetPosition(), summon);
                        break;
                    case ID_DEFENDER_OF_THE_LIGHT:
                        handleSummonedCreatureDeath(defenders_of_the_light, Spawn_Positions_Defender_of_the_Light, NUMBER_DEFENDER_OF_THE_LIGHT, summon);
                        break;
                    case ID_LORD_MAXWELL_TYROSUS:
                        handleSummonedCreatureDeath(maxwell, Spawn_Positions_Lord_Maxwell_Tyrosus, summon);
                        break;
                    case ID_KORFAX_CHAMPION_OF_THE_LIGHT:
                        handleSummonedCreatureDeath(korfax, Spawn_Positions_Lord_Maxwell_Tyrosus, summon);
                        break;
                    case ID_LEONID_BARTHALOMEW_THE_REVERED:
                        handleSummonedCreatureDeath(leonid, Spawn_Positions_Lord_Maxwell_Tyrosus, summon);
                        break;
                    case ID_DUKE_NICHOLAS_ZVERENHOFF:
                        handleSummonedCreatureDeath(nicholas, Spawn_Positions_Lord_Maxwell_Tyrosus, summon);
                        break;
                    case ID_COMMANDER_ELIGOR_DAWNBRINGER:
                        handleSummonedCreatureDeath(eligor, Spawn_Positions_Lord_Maxwell_Tyrosus, summon);
                        break;
                    case ID_RAYNE:
                        handleSummonedCreatureDeath(rayne, Spawn_Positions_Lord_Maxwell_Tyrosus, summon);
                        break;
                    case ID_RIMBLAT_EARTHSHATTER:
                        handleSummonedCreatureDeath(rimblat, Spawn_Positions_Lord_Maxwell_Tyrosus, summon);
                        break;
                    default:
                        break;
                    }
                    break;
                case PHASE_BATTLE_LOST:
                    if (summon_creature_id == ID_DEFENDER_OF_THE_LIGHT)
                    {
                        handleSummonedCreatureDeath(defenders_of_the_light, Spawn_Positions_Defender_of_the_Light, NUMBER_DEFENDER_OF_THE_LIGHT, summon);
                    }
                    else
                    {
                        handleSummonedCreatureDeath(summon);
                        //summon->DespawnOrUnsummon();
                    }
                default:
                    break;
                }
            }

            //triggered when the player selects a gossip option recieved from this npc
            bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
            {
                //determine which gossip action the player selected
                uint32 action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
                //remove any extra options added to this creatures gossip menu for the player
                ClearGossipMenuFor(player);
                //gossip action switch
                switch (action)
                {
                case EVENT_GOSSIP_ACTION_PLAYER_QUEUE:
                    playerList.push_back(player);
                    CloseGossipMenuFor(player);
                    break;
                case EVENT_GOSSIP_ACTION_DEBUG_FOR_COMBAT_TEST:
                    despawnSummons();
                    me->SetFaction(14);
                    me->Dismount();
                    current_phase = PHASE_IN_BATTLE;
                    //me->Say("Entered phase: PHASE_IN_BATTLE", LANG_UNIVERSAL);
                    me->SetReactState(REACT_AGGRESSIVE);
                    CloseGossipMenuFor(player);
                    break;
                default:
                    CloseGossipMenuFor(player);
                    break;
                }

                return true;
            }

            //triggered on player right click while npc has gossip flag
            bool GossipHello(Player* player) override
            {
                if (me->IsQuestGiver())
                {
                    //prepare any quest options for the player if they exist
                    player->PrepareQuestMenu(me->GetGUID());
                }

                //current_phase switch to determine what gossip to send if any
                switch (current_phase)
                {
                case PHASE_WAITING_FOR_PLAYERS:
                case PHASE_WAITING_FOR_BATTLE:
                    //if the player is on the Light of Dawn quest and they haven't completed it
                    if (player->GetQuestStatus(12801) == QUEST_STATUS_INCOMPLETE || player->CanBeGameMaster())
                    {
                        //bool to determine if player is already registered for the event
                        bool playerNotRegistered = true;

                        //if the player list isn't empty, search through it to see if the player is registered already
                        if (!playerList.empty())
                        {
                            for (std::list<Player*>::iterator itr = playerList.begin(); itr != playerList.end(); ++itr)
                            {
                                if (*itr == player)
                                {
                                    playerNotRegistered = false;
                                }
                            }
                        }

                        if (playerNotRegistered)
                        {
                            //add option to queue for the event with select action of EVENT_GOSSIP_ACTION_PLAYER_QUEUE
                            AddGossipItemFor(player, 0, "I am ready for our attack on Light's Hope.", GOSSIP_SENDER_MAIN, EVENT_GOSSIP_ACTION_PLAYER_QUEUE);
                            if (player->CanBeGameMaster())
                            {
                                //add option for combat testing
                                //AddGossipItemFor(player, 0, "Eat my ass.", GOSSIP_SENDER_MAIN, EVENT_GOSSIP_ACTION_DEBUG_FOR_COMBAT_TEST);
                            }
                            //send player the created gossip menu with npc_text id of EVENT_GOSSIP_TEXTID_PLAYER_NOT_REGISTERED
                            SendGossipMenuFor(player, EVENT_GOSSIP_TEXTID_PLAYER_NOT_REGISTERED, me->GetGUID());
                            //me->Say("Player not registered", LANG_UNIVERSAL);
                        }
                        else
                        {
                            //send player the created gossip menu with npc_text id of EVENT_GOSSIP_TEXTID_PLAYER_REGISTERED
                            SendGossipMenuFor(player, EVENT_GOSSIP_TEXTID_PLAYER_REGISTERED, me->GetGUID());
                            //me->Say("Player registered", LANG_UNIVERSAL);
                        }
                    }

                    break;
                case PHASE_EVENT_DONE:
                    SendGossipMenuFor(player, EVENT_GOSSIP_TEXTID_EVENT_DONE, me->GetGUID());
                    break;
                default:
                    break;
                }

                return true;
            }

            void UpdateAI(uint32 diff) override
            {
                if (!events.Empty())
                {
                    events.Update(diff);
                }

                switch (current_phase)
                {
                case PHASE_WAITING_FOR_PLAYERS:
                    while (uint32 eventId = events.ExecuteEvent())
                    {
                        switch (eventId)
                        {
                        case SCRIPT_PHASE_ANY_SET_WEATHER_TO_RAINING_REPEATING:
                        {
                            setZoneWeatherToRaining(true);
                            events.ScheduleEvent(SCRIPT_PHASE_ANY_SET_WEATHER_TO_RAINING_REPEATING, 2s);
                            break;
                        }
                        case SCRIPT_PHASE_ANY_RESPAWN:
                        {
                            //me->Say("respawning", LANG_UNIVERSAL);
                            me->DespawnOrUnsummon();
                            break;
                        }
                        case SCRIPT_PHASE_ANY_DESPAWN_SUMMON_CORPSE:
                        {
                            despawnCorpseOfSummon();
                            break;
                        }
                        default:
                            break;
                        }
                    }

                    if (playerList.size() == EVENT_REQUIREMENT_PLAYERS)
                    {
                        progressEvent();
                    }

                    break;
                case PHASE_WAITING_FOR_BATTLE:
                    while (uint32 eventId = events.ExecuteEvent())
                    {
                        switch (eventId)
                        {
                        case SCRIPT_PHASE_WAITING_FOR_BATTLE_UPDATE_EVENT_COUNTDOWN_WORLDSTATE:
                        {
                            event_countdown_remaining_time -= 1;
                            updateWorldStateForPlayers(WORLD_STATE_COUNTDOWN_TIME, event_countdown_remaining_time);
                            events.ScheduleEvent(SCRIPT_PHASE_WAITING_FOR_BATTLE_UPDATE_EVENT_COUNTDOWN_WORLDSTATE, 60s);
                            break;
                        }
                        case SCRIPT_PHASE_WAITING_FOR_BATTLE_TALK_1:
                        {
                            Talk(DARION_EVENT_WAITING_FOR_BATTLE_1);
                            break;
                        }
                        case SCRIPT_PHASE_WAITING_FOR_BATTLE_TALK_2:
                            Talk(DARION_EVENT_WAITING_FOR_BATTLE_2);
                            break;
                        case SCRIPT_PHASE_WAITING_FOR_BATTLE_TALK_3:
                            Talk(DARION_EVENT_WAITING_FOR_BATTLE_3);
                            break;
                        case SCRIPT_PHASE_WAITING_FOR_BATTLE_TO_PHASE_OPENING_SCENE:
                            progressEvent();
                            updateWorldStateForPlayers(WORLD_STATE_COUNTDOWN_TIME, 0);
                            updateWorldStateForPlayers(WORLD_STATE_COUNTDOWN_ENABLE, 0);
                            updateWorldStateForPlayers(WORLD_STATE_EVENT_BEGIN_ENABLE, 1);
                            updateWorldStateForPlayers(WORLD_STATE_SOLDIERS_ENABLE, 1);
                            updateWorldStateForPlayers(WORLD_STATE_SCOURGE_COUNT, ENCOUNTER_TOTAL_SCOURGE);
                            updateWorldStateForPlayers(WORLD_STATE_DEFENDERS_COUNT, ENCOUNTER_TOTAL_DAWN);
                            break;
                        case SCRIPT_PHASE_ANY_SET_WEATHER_TO_RAINING_REPEATING:
                        {
                            setZoneWeatherToRaining(true);
                            events.ScheduleEvent(SCRIPT_PHASE_ANY_SET_WEATHER_TO_RAINING_REPEATING, 2s);
                            break;
                        }
                        case SCRIPT_PHASE_ANY_RESPAWN:
                        {
                            //me->Say("respawning", LANG_UNIVERSAL);
                            me->DespawnOrUnsummon();
                            break;
                        }
                        case SCRIPT_PHASE_ANY_DESPAWN_SUMMON_CORPSE:
                        {
                            despawnCorpseOfSummon();
                            break;
                        }
                        default:
                            break;
                        }
                    }

                    break;
                case PHASE_OPENING_SCENE:
                    while (uint32 eventId = events.ExecuteEvent())
                    {
                        switch (eventId)
                        {
                        case SCRIPT_PHASE_OPENING_SCENE_TALK_1:
                        {
                            Talk(DARION_EVENT_OPENING_SCENE_1);
                            break;
                        }
                        case SCRIPT_PHASE_OPENING_SCENE_TALK_2:
                        {
                            Talk(DARION_EVENT_OPENING_SCENE_2);
                            break;
                        }
                        case SCRIPT_PHASE_OPENING_SCENE_SUMMON:
                        {
                            summonUnits_OpeningScene();
                            break;
                        }
                        case SCRIPT_PHASE_OPENING_SCENE_SCRIPTED_SUMMONS_ATTACK_ANIMATION:
                        {
                            doAttackAnimationForScriptedSummons();
                            break;
                        }
                        case SCRIPT_PHASE_OPENING_SCENE_SCRIPTED_SUMMONS_COMPLETE_SPAWN:
                        {
                            finalizeSpawningAndCleanupScriptedSummons();
                            break;
                        }
                        case SCRIPT_PHASE_OPENING_SCENE_TALK_3:
                        {
                            Talk(DARION_EVENT_OPENING_SCENE_3);
                            break;
                        }
                        case SCRIPT_PHASE_OPENING_SCENE_SCOURGE_ROAR:
                            summonedUnits_Roar_OpeningScene();
                            break;
                        case SCRIPT_PHASE_OPENING_SCENE_TO_PHASE_CHARGE_INTO_BATTLE:
                            progressEvent();
                            break;
                        case SCRIPT_PHASE_ANY_SET_WEATHER_TO_RAINING_REPEATING:
                        {
                            setZoneWeatherToRaining(true);
                            events.ScheduleEvent(SCRIPT_PHASE_ANY_SET_WEATHER_TO_RAINING_REPEATING, 2s);
                            break;
                        }
                        case SCRIPT_PHASE_ANY_RESPAWN:
                        {
                            //me->Say("respawning", LANG_UNIVERSAL);
                            me->DespawnOrUnsummon();
                            break;
                        }
                        case SCRIPT_PHASE_ANY_DESPAWN_SUMMON_CORPSE:
                        {
                            despawnCorpseOfSummon();
                            break;
                        }
                        default:
                            break;
                        }
                    }

                    break;
                case PHASE_CHARGE_INTO_BATTLE:
                    while (uint32 eventId = events.ExecuteEvent())
                    {
                        switch (eventId)
                        {
                        case SCRIPT_PHASE_OPENING_SCENE_SCRIPTED_SUMMONS_ATTACK_ANIMATION:
                        {
                            doAttackAnimationForScriptedSummons();
                            break;
                        }
                        case SCRIPT_PHASE_OPENING_SCENE_SCRIPTED_SUMMONS_COMPLETE_SPAWN:
                        {
                            finalizeSpawningAndCleanupScriptedSummons();
                            break;
                        }
                        case SCRIPT_PHASE_CHARGING_INTO_BATTLE_TO_IN_BATTLE:
                            progressEvent();
                            break;
                        case SCRIPT_PHASE_ANY_SET_WEATHER_TO_RAINING_REPEATING:
                        {
                            setZoneWeatherToRaining(true);
                            events.ScheduleEvent(SCRIPT_PHASE_ANY_SET_WEATHER_TO_RAINING_REPEATING, 2s);
                            break;
                        }
                        case SCRIPT_PHASE_ANY_RESPAWN:
                        {
                            me->DespawnOrUnsummon();
                            break;
                        }
                        case SCRIPT_PHASE_ANY_DESPAWN_SUMMON_CORPSE:
                        {
                            despawnCorpseOfSummon();
                            break;
                        }
                        default:
                            break;
                        }
                    }

                    break;
                case PHASE_IN_BATTLE:
                    //for npcs that need to do things at the invincibility hp level
                    if (me->GetHealth() == INVINCIBILITY_HP)
                    {
                        me->SetHealth(me->GetMaxHealth());
                    }

                    //main combat loop
                    if (me->GetReactState() == REACT_AGGRESSIVE)
                    {
                        //if the unit is already in combat and has a target that they are attacking
                        if (me->IsInCombat() && me->GetVictim())
                        {
                            //potential fix for combat crashing that's been happeneing
                            if (!(me->GetVictim()->IsAlive()) || !(me->GetVictim()->IsInWorld()))
                            {
                                updateInCombatWithList();
                                Unit *target = me->GetCombatManager().GetAnyTarget();
                                me->GetMotionMaster()->MoveChase(target);
                                me->Attack(target, true);

                                if (casting)
                                {
                                    tempTarget1 = target;
                                }
                            }

                            //used for initiation of spell cast scripts 
                            if (first_inCombat_ever)
                            {
                                events.ScheduleEvent(SCRIPT_PHASE_IN_BATTLE_DARION_TALK, (TIMER_HIGHLORD_DARION_MOGRAINE_DEATHS_TALK_FIRST * 1s));
                                events.ScheduleEvent(SCRIPT_PHASE_IN_BATTLE_CAST_DEATHS_EMBRACE, (TIMER_HIGHLORD_DARION_MOGRAINE_DEATHS_EMBRACE_FIRST * 1s));
                                events.ScheduleEvent(SCRIPT_PHASE_IN_BATTLE_CAST_ICY_TOUCH, (TIMER_HIGHLORD_DARION_MOGRAINE_ICY_TOUCH_FIRST * 1s));
                                events.ScheduleEvent(SCRIPT_PHASE_IN_BATTLE_CAST_UNHOLY_BLIGHT, (TIMER_HIGHLORD_DARION_MOGRAINE_UNHOLY_BLIGHT_FIRST * 1s));
                                events.ScheduleEvent(SCRIPT_PHASE_IN_BATTLE_CAST_ANTI_MAGIC_ZONE, (TIMER_HIGHLORD_DARION_MOGRAINE_ANTI_MAGIC_ZONE_FIRST * 1s));

                                first_inCombat_ever = false;
                            }

                            if (first_inCombat_recent)
                            {
                                events.CancelEvent(SCRIPT_IN_BATTLE_UPDATE_TARGET_LIST);
                                first_outOfCombat_recent = true;
                            }

                            //if the unit's auto attack is ready, they are in range of their target and they are not set to IDLE_MOTION_TYPE due to spell casting
                            if (me->isAttackReady() && me->IsWithinMeleeRange(me->GetVictim()) && !casting)
                            {
                                //melee attack the target
                                me->AttackerStateUpdate(me->GetVictim(), BASE_ATTACK);
                                //reset the auto attack timer
                                me->resetAttackTimer();
                            }

                            //used for handling every combat event
                            while (uint32 eventId = events.ExecuteEvent())
                            {
                                switch (eventId)
                                {
                                case SCRIPT_PHASE_IN_BATTLE_DARION_TALK:
                                    Talk(DARION_IN_BATTLE);
                                    events.ScheduleEvent(SCRIPT_PHASE_IN_BATTLE_DARION_TALK, (TIMER_HIGHLORD_DARION_MOGRAINE_DEATHS_TALK_REPEAT * 1s));
                                    break;
                                case SCRIPT_PHASE_IN_BATTLE_CAST_DEATHS_EMBRACE:
                                    highlordDarionMograine_cast_deathsEmbrace();
                                    break;
                                case SCRIPT_PHASE_IN_BATTLE_CAST_ICY_TOUCH:
                                    highlordDarionMograine_cast_icyTouch();
                                    break;
                                case SCRIPT_PHASE_IN_BATTLE_CAST_UNHOLY_BLIGHT:
                                    highlordDarionMograine_cast_unholyBlight();
                                    break;
                                case SCRIPT_PHASE_IN_BATTLE_CAST_ANTI_MAGIC_ZONE:
                                    highlordDarionMograine_cast_antiMagicZone();
                                    break;
                                case SCRIPT_IN_BATTLE_UPDATE_TARGET_LIST:
                                    updateInCombatWithList();
                                    break;
                                case SCRIPT_PHASE_IN_BATTLE_SUMMON_RAMPAGING_ABOMINATIONS:
                                    summonRampagingAbominations();
                                    break;
                                case SCRIPT_PHASE_IN_BATTLE_START_LOSING_BATTLE:
                                    scourgeStartLosingBattle();
                                    break;
                                case SCRIPT_PHASE_IN_BATTLE_KILL_ALL_SCOURGE_UNITS:
                                    killAllScourgeUnits(false);
                                    break;
                                case SCRIPT_PHASE_IN_BATTLE_ORBAZ_FLEES:
                                    orbazFleeBattle();
                                    break;
                                case SCRIPT_PHASE_IN_BATTLE_ORBAZ_DESPAWN:
                                    orbaz->DespawnOrUnsummon();
                                    orbaz = nullptr;
                                    orbaz_spawned = false;
                                    break;
                                case SCRIPT_PHASE_IN_BATTLE_TIRION_MOVE_TO_LIGHTS_HOPE:
                                    tirion->GetMotionMaster()->MovePoint(0, highlord_tirion_fordring_to_lights_hope, true);
                                    break;
                                case SCRIPT_PHASE_IN_BATTLE_TO_BATTLE_LOST:
                                    progressEvent();
                                    break;
                                case SCRIPT_PHASE_OPENING_SCENE_SCRIPTED_SUMMONS_ATTACK_ANIMATION:
                                    doAttackAnimationForScriptedSummons();
                                    break;
                                case SCRIPT_PHASE_OPENING_SCENE_SCRIPTED_SUMMONS_COMPLETE_SPAWN:
                                    finalizeSpawningAndCleanupScriptedSummons();
                                    break;
                                case SCRIPT_PHASE_ANY_SET_WEATHER_TO_RAINING_REPEATING:
                                    setZoneWeatherToRaining(true);
                                    events.ScheduleEvent(SCRIPT_PHASE_ANY_SET_WEATHER_TO_RAINING_REPEATING, 2s);
                                    break;
                                case SCRIPT_PHASE_ANY_RESPAWN:
                                    //me->Say("respawning", LANG_UNIVERSAL);
                                    me->DespawnOrUnsummon();
                                    break;
                                case SCRIPT_PHASE_ANY_DESPAWN_SUMMON_CORPSE:
                                    despawnCorpseOfSummon();
                                    break;
                                default:
                                    break;
                                }
                            }
                        }
                        else if (me->IsInCombat() && !me->GetVictim())
                        {
                            //me->Say("In combat, no target.", LANG_UNIVERSAL);
                            if (first_inCombat_recent)
                            {
                                events.CancelEvent(SCRIPT_IN_BATTLE_UPDATE_TARGET_LIST);
                                first_outOfCombat_recent = true;
                            }
                            Unit *target = me->GetCombatManager().GetAnyTarget();
                            me->GetMotionMaster()->MoveChase(target);
                            me->Attack(target, true);
                        }
                        else if (!me->IsInCombat())
                        {
                            //me->Say("Not in combat.", LANG_UNIVERSAL);
                            //this is to prevent script spamming and potentially bogging down the server with too many updateInCombatWithList() calls
                            if (first_outOfCombat_recent)
                            {
                                me->GetMotionMaster()->Clear();
                                me->GetMotionMaster()->MoveIdle();
                                updateInCombatWithList();
                                events.ScheduleEvent(SCRIPT_IN_BATTLE_UPDATE_TARGET_LIST, 1s);
                                first_outOfCombat_recent = false;
                                first_inCombat_recent = true;
                            }

                            //this block is used to handle in combat events that fire off while not in combat
                            //the general idea here is to continually reschedule the event until the unit is back in combat and then can actually execute the event
                            while (uint32 eventId = events.ExecuteEvent())
                            {
                                switch (eventId)
                                {
                                case SCRIPT_PHASE_IN_BATTLE_DARION_TALK:
                                    Talk(DARION_IN_BATTLE);
                                    events.ScheduleEvent(SCRIPT_PHASE_IN_BATTLE_DARION_TALK, (TIMER_HIGHLORD_DARION_MOGRAINE_DEATHS_TALK_REPEAT * 1s));
                                    break;
                                case SCRIPT_PHASE_IN_BATTLE_CAST_DEATHS_EMBRACE:
                                    //me->Say("out of combat, rescheduling deaths embrace by 1s", LANG_UNIVERSAL);
                                    events.ScheduleEvent(SCRIPT_PHASE_IN_BATTLE_CAST_DEATHS_EMBRACE, 1s);
                                    break;
                                case SCRIPT_PHASE_IN_BATTLE_CAST_ICY_TOUCH:
                                    //me->Say("out of combat, rescheduling icy touch by 1s", LANG_UNIVERSAL);
                                    events.ScheduleEvent(SCRIPT_PHASE_IN_BATTLE_CAST_ICY_TOUCH, 1s);
                                    break;
                                case SCRIPT_PHASE_IN_BATTLE_CAST_UNHOLY_BLIGHT:
                                    //me->Say("out of combat, rescheduling unholy blight by 1s", LANG_UNIVERSAL);
                                    events.ScheduleEvent(SCRIPT_PHASE_IN_BATTLE_CAST_UNHOLY_BLIGHT, 1s);
                                    break;
                                case SCRIPT_PHASE_IN_BATTLE_CAST_ANTI_MAGIC_ZONE:
                                    //me->Say("out of combat, rescheduling anti magic zone by 1s", LANG_UNIVERSAL);
                                    events.ScheduleEvent(SCRIPT_PHASE_IN_BATTLE_CAST_ANTI_MAGIC_ZONE, 1s);
                                    break;
                                case SCRIPT_IN_BATTLE_UPDATE_TARGET_LIST:
                                    updateInCombatWithList();
                                    events.ScheduleEvent(SCRIPT_IN_BATTLE_UPDATE_TARGET_LIST, 1s);
                                    break;
                                case SCRIPT_PHASE_IN_BATTLE_SUMMON_RAMPAGING_ABOMINATIONS:
                                    summonRampagingAbominations();
                                    break;
                                case SCRIPT_PHASE_IN_BATTLE_START_LOSING_BATTLE:
                                    scourgeStartLosingBattle();
                                    break;
                                case SCRIPT_PHASE_IN_BATTLE_KILL_ALL_SCOURGE_UNITS:
                                    killAllScourgeUnits(false);
                                    break;
                                case SCRIPT_PHASE_IN_BATTLE_ORBAZ_FLEES:
                                    orbazFleeBattle();
                                    break;
                                case SCRIPT_PHASE_IN_BATTLE_TO_BATTLE_LOST:
                                    progressEvent();
                                    break;
                                case SCRIPT_PHASE_IN_BATTLE_ORBAZ_DESPAWN:
                                    orbaz->DespawnOrUnsummon();
                                    orbaz = nullptr;
                                    orbaz_spawned = false;
                                    break;
                                case SCRIPT_PHASE_IN_BATTLE_TIRION_MOVE_TO_LIGHTS_HOPE:
                                    tirion->GetMotionMaster()->MovePoint(0, highlord_tirion_fordring_to_lights_hope, true);
                                    break;
                                case SCRIPT_PHASE_OPENING_SCENE_SCRIPTED_SUMMONS_ATTACK_ANIMATION:
                                    doAttackAnimationForScriptedSummons();
                                    break;
                                case SCRIPT_PHASE_OPENING_SCENE_SCRIPTED_SUMMONS_COMPLETE_SPAWN:
                                    finalizeSpawningAndCleanupScriptedSummons();
                                    break;
                                case SCRIPT_PHASE_ANY_SET_WEATHER_TO_RAINING_REPEATING:
                                    setZoneWeatherToRaining(true);
                                    events.ScheduleEvent(SCRIPT_PHASE_ANY_SET_WEATHER_TO_RAINING_REPEATING, 2s);
                                    break;
                                case SCRIPT_PHASE_ANY_RESPAWN:
                                    //me->Say("respawning", LANG_UNIVERSAL);
                                    me->DespawnOrUnsummon();
                                    break;
                                case SCRIPT_PHASE_ANY_DESPAWN_SUMMON_CORPSE:
                                    despawnCorpseOfSummon();
                                    break;
                                default:
                                    break;
                                }
                            }
                        }
                    }
                    else
                    {
                        while (uint32 eventId = events.ExecuteEvent())
                        {
                            switch (eventId)
                            {
                            case SCRIPT_PHASE_OPENING_SCENE_SCRIPTED_SUMMONS_ATTACK_ANIMATION:
                                doAttackAnimationForScriptedSummons();
                                break;
                            case SCRIPT_PHASE_OPENING_SCENE_SCRIPTED_SUMMONS_COMPLETE_SPAWN:
                                finalizeSpawningAndCleanupScriptedSummons();
                                break;
                            case SCRIPT_PHASE_ANY_SET_WEATHER_TO_RAINING_REPEATING:
                                setZoneWeatherToRaining(true);
                                events.ScheduleEvent(SCRIPT_PHASE_ANY_SET_WEATHER_TO_RAINING_REPEATING, 2s);
                                break;
                            case SCRIPT_PHASE_ANY_RESPAWN:
                                //me->Say("respawning", LANG_UNIVERSAL);
                                me->DespawnOrUnsummon();
                                break;
                            case SCRIPT_PHASE_ANY_DESPAWN_SUMMON_CORPSE:
                                despawnCorpseOfSummon();
                                break;
                            default:
                                break;
                            }
                        }
                    }

                    if (remaining_argent_dawn <= NUMBER_DAWN_FORCES_FOR_BATTLE_END && !tirion_spawned)
                    {
                        tirion = me->SummonCreature(ID_HIGHLORD_TIRION_FORDRING, Spawn_Positions_Highlord_Tirion_Fordring, TEMPSUMMON_MANUAL_DESPAWN);
                        tirion_spawned = true;
                        tirion->LoadEquipment(0, true);
                        tirion->AI()->Talk(TIRION_EVENT_SPAWNED);
                        events.ScheduleEvent(SCRIPT_PHASE_IN_BATTLE_START_LOSING_BATTLE, 5s);
                        events.ScheduleEvent(SCRIPT_PHASE_IN_BATTLE_KILL_ALL_SCOURGE_UNITS, 10s);
                        events.ScheduleEvent(SCRIPT_PHASE_IN_BATTLE_KILL_ALL_SCOURGE_UNITS, 21s);
                        events.ScheduleEvent(SCRIPT_PHASE_IN_BATTLE_ORBAZ_FLEES, 25s);
                        events.ScheduleEvent(SCRIPT_PHASE_IN_BATTLE_TIRION_MOVE_TO_LIGHTS_HOPE, 28s);
                        events.ScheduleEvent(SCRIPT_PHASE_IN_BATTLE_ORBAZ_DESPAWN, 35s);
                        events.ScheduleEvent(SCRIPT_PHASE_IN_BATTLE_KILL_ALL_SCOURGE_UNITS, 30s);
                        events.ScheduleEvent(SCRIPT_PHASE_IN_BATTLE_TO_BATTLE_LOST, 39s);
                        events.ScheduleEvent(SCRIPT_PHASE_IN_BATTLE_KILL_ALL_SCOURGE_UNITS, 41s);
                    }

                    break;
                case PHASE_BATTLE_LOST:
                    while (uint32 eventId = events.ExecuteEvent())
                    {
                        switch (eventId)
                        {
                        case SCRIPT_PHASE_IN_BATTLE_KILL_ALL_SCOURGE_UNITS:
                            killAllScourgeUnits(true);
                            break;
                        case SCRIPT_PHASE_BATTLE_LOST_SETUP_NPCS:
                            setupForBattleLost();
                            break;
                        case SCRIPT_PHASE_BATTLE_LOST_TIRION_TALK_1:
                            tirion->AI()->Talk(TIRION_BATTLE_LOST_1);
                            break;
                        case SCRIPT_PHASE_BATTLE_LOST_EVERYONE_MOVE_TO_POSITIONS:
                            battleLostEveryoneMoveToPostions();
                            break;
                        case SCRIPT_PHASE_BATTLE_LOST_DARION_TALK_1:
                            Talk(DARION_BATTLE_LOST_1);
                            break;
                        case SCRIPT_PHASE_BATTLE_LOST_DKS_STAND_DOWN:
                            koltira->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STAND_STATE_NONE);
                            koltira->HandleEmoteCommand(EMOTE_STAND_STATE_NONE);
                            thassarian->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STAND_STATE_NONE);
                            thassarian->HandleEmoteCommand(EMOTE_STAND_STATE_NONE);
                            break;
                        case SCRIPT_PHASE_BATTLE_LOST_DARION_KNEEL:
                            Talk(DARION_KNEEL_BEFORE_TIRION);
                            me->CastSpell(me, SPELL_KNEEL);
                            break;
                        case SCRIPT_PHASE_BATTLE_LOST_DKS_KNEEL:
                            koltira->CastSpell(koltira, SPELL_KNEEL);
                            thassarian->CastSpell(thassarian, SPELL_KNEEL);
                            break;
                        case SCRIPT_PHASE_BATTLE_LOST_TIRON_TALK_2:
                            tirion->AI()->Talk(TIRION_BATTLE_LOST_2);
                            break;
                        case SCRIPT_PHASE_BATTLE_LOST_TIRON_TALK_3:
                            tirion->AI()->Talk(TIRION_BATTLE_LOST_3);
                            break;
                        case SCRIPT_PHASE_BATTLE_LOST_TIRON_TALK_4:
                            tirion->AI()->Talk(TIRION_BATTLE_LOST_4);
                            break;
                        case SCRIPT_PHASE_BATTLE_LOST_DIRION_TALK_2:
                            me->RemoveAurasDueToSpell(SPELL_KNEEL);
                            Talk(DARION_BATTLE_LOST_2);
                            break;
                        case SCRIPT_PHASE_BATTLE_LOST_DIRION_POINT_AT_TIRION:
                            me->HandleEmoteCommand(EMOTE_ONESHOT_POINT_NO_SHEATHE);
                            break;
                        case SCRIPT_PHASE_BATTLE_LOST_TO_PHASE_FLASH_BACK:
                            progressEvent();
                            break;
                        case SCRIPT_PHASE_ANY_SET_WEATHER_TO_RAINING_REPEATING:
                        {
                            setZoneWeatherToRaining(true);
                            events.ScheduleEvent(SCRIPT_PHASE_ANY_SET_WEATHER_TO_RAINING_REPEATING, 2s);
                            break;
                        }
                        case SCRIPT_PHASE_ANY_RESPAWN:
                        {
                            me->DespawnOrUnsummon();
                            break;
                        }
                        case SCRIPT_PHASE_ANY_DESPAWN_SUMMON_CORPSE:
                        {
                            despawnCorpseOfSummon();
                            break;
                        }
                        default:
                            break;
                        }
                    }

                    break;
                case PHASE_FLASH_BACK:
                    while (uint32 eventId = events.ExecuteEvent())
                    {
                        switch (eventId)
                        {
                        case SCRIPT_PHASE_FLASH_BACK_ALEXANDROS_TALK_1:
                            alexandros->AI()->Talk(ALEXANDROS_FLASH_BACK_1);
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_DARION_TURN_TO_FACE_ALEXANDROS:
                            me->SetFacingTo(1.56f);
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_DARION_TALK_1:
                            Talk(DARION_FLASH_BACK_1);
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_SPAWN_YOUNG_DARION:
                            young_mograine = me->SummonCreature(ID_YOUNG_DARION_MOGRAINE, Spawn_Positions_Young_Darion, TEMPSUMMON_MANUAL_DESPAWN);
                            young_mograine_spawned = true;
                            me->CastSpell(me, SPELL_KNEEL);
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_DARION_TALK_2:
                            Talk(DARION_FLASH_BACK_2);
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_YOUNG_DARION_TALK_1:
                            young_mograine->AI()->Talk(YOUNG_DARION_FLASH_BACK_1);
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_YOUNG_DARION_RUN_TO_ALEXANDROS:
                            young_mograine->GetMotionMaster()->MovePoint(0, young_darion_to_alexandros_mograine, true);
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_YOUNG_DARION_TALK_2:
                            young_mograine->AI()->Talk(YOUNG_DARION_FLASH_BACK_2);
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_YOUNG_DARION_TALK_3:
                            young_mograine->AI()->Talk(YOUNG_DARION_FLASH_BACK_3);
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_ALEXANDROS_TALK_2:
                            alexandros->AI()->Talk(ALEXANDROS_FLASH_BACK_2);
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_YOUNG_DARION_TALK_4:
                            young_mograine->AI()->Talk(YOUNG_DARION_FLASH_BACK_4);
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_ALEXANDROS_TALK_3:
                            alexandros->AI()->Talk(ALEXANDROS_FLASH_BACK_3);
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_TIRION_WALK_NEAR_DARION:
                            tirion->SetWalk(true);
                            tirion->GetMotionMaster()->MovePoint(0, tirion_to_near_darion, true);
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_YOUNG_DARION_TALK_5:
                            young_mograine->AI()->Talk(YOUNG_DARION_FLASH_BACK_5);
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_ALEXANDROS_TALK_4:
                            alexandros->AI()->Talk(ALEXANDROS_FLASH_BACK_4);
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_ALEXANDROS_TALK_5:
                            young_mograine->DespawnOrUnsummon();
                            young_mograine_spawned = false;
                            alexandros->AI()->Talk(ALEXANDROS_FLASH_BACK_5);
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_LICH_KING_SPAWN:
                            lich_king = me->SummonCreature(ID_THE_LICH_KING, Spawn_Positions_Lich_King, TEMPSUMMON_MANUAL_DESPAWN);
                            lich_king_spawned = true;
                            lich_king->SetReactState(REACT_AGGRESSIVE);
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_LICH_KING_TALK_1:
                            lich_king->AI()->Talk(LICH_KING_FLASH_BACK_1);
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_LICH_KING_TALK_2:
                            for (unsigned int x = 0; x < NUMBER_DEFENDER_OF_THE_LIGHT; x++)
                            {
                                defenders_of_the_light[x]->SetFacingToObject(lich_king);
                            }

                            maxwell->SetFacingToObject(lich_king);
                            maxwell->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_READY2H);
                            maxwell->HandleEmoteCommand(EMOTE_STATE_READY2H);

                            korfax->SetFacingToObject(lich_king);
                            korfax->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_READY2H);
                            korfax->HandleEmoteCommand(EMOTE_STATE_READY2H);

                            leonid->SetFacingToObject(lich_king);
                            leonid->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_READY2H);
                            leonid->HandleEmoteCommand(EMOTE_STATE_READY2H);

                            nicholas->SetFacingToObject(lich_king);
                            nicholas->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_READY2H);
                            nicholas->HandleEmoteCommand(EMOTE_STATE_READY2H);

                            eligor->SetFacingToObject(lich_king);
                            eligor->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_READY2H);
                            eligor->HandleEmoteCommand(EMOTE_STATE_READY2H);

                            rayne->SetFacingToObject(lich_king);
                            rayne->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_READY2H);
                            rayne->HandleEmoteCommand(EMOTE_STATE_READY2H);

                            rimblat->SetFacingToObject(lich_king);
                            rimblat->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_READY2H);
                            rimblat->HandleEmoteCommand(EMOTE_STATE_READY2H);

                            lich_king->AI()->Talk(LICH_KING_FLASH_BACK_2);
                            lich_king->CastSpell(alexandros, SPELL_DRAIN_ALEXANDROS);
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_ALEXANDROS_DESPAWN:
                            alexandros->DespawnOrUnsummon();
                            alexandros_spawned = false;
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_DARION_STAND_UP:
                            me->RemoveAurasDueToSpell(SPELL_KNEEL);
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_DARION_TALK_3:
                            Talk(DARION_FLASH_BACK_3);
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_LICH_KING_WALK_FORWARD:
                            lich_king->SetWalk(true);
                            lich_king->GetMotionMaster()->MovePoint(0, lich_king_closer_to_tirion, true);
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_DARION_CHARGE_AT_LICH_KING:
                            me->CastSpell(lich_king, SPELL_DARION_CHARGE_AT_LICH_KING);
                            lich_king->HandleEmoteCommand(EMOTE_ONESHOT_ATTACK2H_LOOSE);
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_DARION_KNOCKED_BACK:
                            lich_king->AI()->Talk(LICH_KING_FLASH_BACK_3);
                            me->GetMotionMaster()->MoveJump(darion_kockback_position, 40.0f, 8.0f);
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_DARION_KNEEL_AFTER_KNOCKBACK:
                            me->SetFacingTo(darion_kockback_position.GetOrientation(), true);
                            me->CastSpell(me, SPELL_KNEEL);
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_TIRION_TALK_1:
                            tirion->AI()->Talk(TIRION_FLASH_BACK_1);
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_LICH_KING_LAUGH:
                            lich_king->HandleEmoteCommand(EMOTE_ONESHOT_LAUGH);
                            lich_king->PlayDirectSound(14820);
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_LICH_KING_TALK_3:
                            lich_king->AI()->Talk(LICH_KING_FLASH_BACK_4);
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_LICH_KING_POINT_AT_TIRION:
                            lich_king->HandleEmoteCommand(EMOTE_ONESHOT_POINT);
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_LICH_KING_TALK_4:
                            lich_king->AI()->Talk(LICH_KING_FLASH_BACK_5);
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_LICH_KING_DRAIN_TIRION:
                            lich_king->CastSpell(tirion, SPELL_DRAIN_TIRION);
                            tirion->AI()->Talk(TIRION_FLASH_BACK_12);
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_ALL_DAWN_ATTACK_LICH_KING:
                            maxwell->AI()->Talk(MAXWELL_FLASH_BACK_1);

                            for (unsigned int x = 0; x < NUMBER_DEFENDER_OF_THE_LIGHT; x++)
                            {
                                defenders_of_the_light[x]->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_PACIFIED);
                                defenders_of_the_light[x]->GetMotionMaster()->MoveChase(lich_king);
                                defenders_of_the_light[x]->Attack(lich_king, true);
                            }

                            maxwell->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_PACIFIED);
                            maxwell->GetMotionMaster()->MoveChase(lich_king);
                            maxwell->Attack(lich_king, true);

                            korfax->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_PACIFIED);
                            korfax->GetMotionMaster()->MoveChase(lich_king);
                            korfax->Attack(lich_king, true);
                            
                            leonid->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_PACIFIED);
                            leonid->GetMotionMaster()->MoveChase(lich_king);
                            leonid->Attack(lich_king, true);
                            
                            nicholas->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_PACIFIED);
                            nicholas->GetMotionMaster()->MoveChase(lich_king);
                            nicholas->Attack(lich_king, true);

                            eligor->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_PACIFIED);
                            eligor->GetMotionMaster()->MoveChase(lich_king);
                            eligor->Attack(lich_king, true);

                            rayne->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_PACIFIED);
                            rayne->GetMotionMaster()->MoveChase(lich_king);
                            rayne->Attack(lich_king, true);

                            rimblat->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_PACIFIED);
                            rimblat->GetMotionMaster()->MoveChase(lich_king);
                            rimblat->Attack(lich_king, true);

                            //lich_king->SetControlled(true, UNIT_STATE_ROOT);
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_LICH_CAST_APOCOLYPSE_ON_ALL_DAWN:
                            lich_king->AI()->Talk(LICH_KING_FLASH_BACK_6);
                            lich_king->CastSpell(lich_king, SPELL_APOCALYPSE, true);
                            //lich_king->CastSpell(lich_king, SPELL_APOCALYPSE_SECONDARY, false);
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_ALL_DAWN_KNOCKED_DOWN:
                            me->GetMotionMaster()->Clear();
                            me->GetMotionMaster()->MoveIdle();
                            me->CombatStop();
                            me->GetCombatManager().EndAllCombat();
                            //lich_king->SetControlled(false, UNIT_STATE_ROOT);
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_DARION_TALK_4:
                            me->RemoveAurasDueToSpell(SPELL_KNEEL);
                            Talk(DARION_FLASH_BACK_4);
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_DARION_TALK_5:
                            me->SetFacingToObject(tirion);
                            Talk(DARION_FLASH_BACK_5);
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_DARION_THROW_ASHBRINGER_AT_TIRION:
                            me->LoadEquipment(0, true);
                            me->CastSpell(tirion, SPELL_THROW_ASHBRINGER, true);
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_DARION_COLLAPSE:
                            Talk(DARION_COLLAPSE);
                            me->CastSpell(me, SPELL_FEIGN_DEATH, true);
                            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_TIRION_PURIFIES_ASHBRINGER:
                            tirion->RemoveAurasDueToSpell(SPELL_DRAIN_TIRION);
                            tirion->CastSpell(tirion, SPELL_REBIRTH_OF_THE_ASHBRINGER, true);
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_TIRION_EQUIPS_ASHBRINGER:
                            tirion->SetSheath(SHEATH_STATE_MELEE);
                            tirion->LoadEquipment(1, true);
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_TIRION_TALK_2:
                            tirion->RemoveAurasDueToSpell(SPELL_REBIRTH_OF_THE_ASHBRINGER);
                            light_of_dawn = me->SummonGameObject(OBJECT_LIGHT_OF_DAWN, tirion->GetPosition(), QuaternionData(), GO_SUMMON_TIMED_OR_CORPSE_DESPAWN);
                            light_of_dawn_spawned = true;
                            tirion->HandleEmoteCommand(EMOTE_ONESHOT_ROAR);
                            tirion->AI()->Talk(TIRION_FLASH_BACK_2);
                            events.CancelEvent(SCRIPT_PHASE_ANY_SET_WEATHER_TO_RAINING_REPEATING);
                            setZoneWeatherToRaining(false);
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_LICH_KING_TALK_5:
                            lich_king->AI()->Talk(LICH_KING_FLASH_BACK_7);
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_TIRION_TALK_3:
                            tirion->AI()->Talk(TIRION_FLASH_BACK_3);
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_TIRION_CHARGE_AT_LICH_KING:
                            tirion->SetWalk(false);
                            lich_king->SetWalk(false);
                            tirion->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_PACIFIED | UNIT_FLAG_SILENCED);
                            tirion->CastSpell(lich_king, SPELL_DARION_CHARGE_AT_LICH_KING, false);
                            //tirion->HandleEmoteCommand(EMOTE_ONESHOT_ATTACK2HTIGHT);
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_TIRION_LAND_FROM_CHARGE:
                            tirion->HandleEmoteCommand(EMOTE_ONESHOT_ATTACK2H_LOOSE);
                            tirion->CastSpell(lich_king, SPELL_TIRION_CHARGE, true);
                            //lich_king->GetMotionMaster()->MoveKnockbackFrom(tirion->GetPositionX(), tirion->GetPositionY(), 40.0f, 8.0f);
                            lich_king->SetHealth((lich_king->GetMaxHealth() * 0.4));
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_LICH_KING_TALK_6:
                            tirion->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_READY2H);
                            tirion->HandleEmoteCommand(EMOTE_STATE_READY2H);
                            lich_king->AI()->Talk(LICH_KING_FLASH_BACK_8);
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_LICH_KING_TALK_7:
                            lich_king->AI()->Talk(LICH_KING_FLASH_BACK_9);
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_LICH_KING_TALK_8:
                            lich_king->AI()->Talk(LICH_KING_FLASH_BACK_10);
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_LICH_KING_CAST_DESPAWN_SPELL:
                            lich_king->CastSpell(lich_king, SPELL_EXIT_TELEPORT_VISUAL, true);
                            tirion->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STAND_STATE_NONE);
                            tirion->HandleEmoteCommand(EMOTE_STAND_STATE_NONE);
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_LICH_KING_DESPAWN:
                            lich_king->DespawnOrUnsummon();
                            lich_king_spawned = false;
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_TIRION_WALK_TO_DARION:
                            //tirion->SetSheath(SHEATH_STATE_UNARMED);
                            tirion->SetFaction(35);

                            for (unsigned int x = 0; x < NUMBER_DEFENDER_OF_THE_LIGHT; x++)
                            {
                                defenders_of_the_light[x]->SetFaction(35);
                            }

                            maxwell->SetFaction(35);
                            maxwell->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                            maxwell->RemoveAurasDueToSpell(SPELL_APOCALYPSE_SECONDARY);
                            maxwell->CastSpell(maxwell, SPELL_KNEEL, true);

                            korfax->SetFaction(35);
                            korfax->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                            korfax->RemoveAurasDueToSpell(SPELL_APOCALYPSE_SECONDARY);
                            korfax->CastSpell(korfax, SPELL_KNEEL, true);

                            leonid->SetFaction(35);
                            leonid->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                            leonid->RemoveAurasDueToSpell(SPELL_APOCALYPSE_SECONDARY);
                            leonid->CastSpell(leonid, SPELL_KNEEL, true);

                            nicholas->SetFaction(35);
                            nicholas->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                            nicholas->RemoveAurasDueToSpell(SPELL_APOCALYPSE_SECONDARY);
                            nicholas->CastSpell(nicholas, SPELL_KNEEL, true);

                            eligor->SetFaction(35);
                            eligor->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                            eligor->RemoveAurasDueToSpell(SPELL_APOCALYPSE_SECONDARY);
                            eligor->CastSpell(eligor, SPELL_KNEEL, true);

                            rayne->SetFaction(35);
                            rayne->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                            rayne->RemoveAurasDueToSpell(SPELL_APOCALYPSE_SECONDARY);
                            rayne->CastSpell(rayne, SPELL_KNEEL, true);

                            rimblat->SetFaction(35);
                            rimblat->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                            rimblat->RemoveAurasDueToSpell(SPELL_APOCALYPSE_SECONDARY);
                            rimblat->CastSpell(rimblat, SPELL_KNEEL, true);

                            tirion->GetMotionMaster()->MovePoint(2, tirion_to_darion_to_heal, true);
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_TIRION_CAST_LAY_ON_HANDS_ON_DARION:
                            tirion->CastSpell(me, SPELL_LAY_ON_HANDS, true);
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_TIRION_TALK_4:
                            tirion->AI()->Talk(TIRION_FLASH_BACK_4);
                            me->RemoveAurasDueToSpell(SPELL_FEIGN_DEATH);
                            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                            me->CastSpell(me, SPELL_KNEEL, true);
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_TIRION_WALK_AWAY_FROM_DARION:
                            tirion->SetWalk(true);
                            tirion->GetMotionMaster()->MovePoint(3, tirion_to_speech_position, true);
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_TIRION_TALK_5:
                            tirion->AI()->Talk(TIRION_FLASH_BACK_5);

                            maxwell->RemoveAurasDueToSpell(SPELL_KNEEL);
                            maxwell->SetWalk(true);
                            maxwell->GetMotionMaster()->MovePoint(2, maxwell_final_position, true);

                            korfax->RemoveAurasDueToSpell(SPELL_KNEEL);
                            korfax->SetWalk(true);
                            korfax->GetMotionMaster()->MovePoint(2, korfax_final_position, true);

                            leonid->RemoveAurasDueToSpell(SPELL_KNEEL);
                            leonid->SetWalk(true);
                            leonid->GetMotionMaster()->MovePoint(2, leonid_final_position, true);

                            nicholas->RemoveAurasDueToSpell(SPELL_KNEEL);
                            nicholas->SetWalk(true);
                            nicholas->GetMotionMaster()->MovePoint(2, nicholas_final_position, true);

                            eligor->RemoveAurasDueToSpell(SPELL_KNEEL);
                            eligor->SetWalk(true);
                            eligor->GetMotionMaster()->MovePoint(2, eligor_final_position, true);

                            rayne->RemoveAurasDueToSpell(SPELL_KNEEL);
                            rayne->SetWalk(true);
                            rayne->GetMotionMaster()->MovePoint(2, rayne_final_position, true);

                            rimblat->RemoveAurasDueToSpell(SPELL_KNEEL);
                            rimblat->SetWalk(true);
                            rimblat->GetMotionMaster()->MovePoint(2, rimblat_final_position, true);
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_TIRION_TALK_6:
                            tirion->AI()->Talk(TIRION_FLASH_BACK_6);
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_TIRION_TALK_7:
                            tirion->AI()->Talk(TIRION_FLASH_BACK_7);
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_TIRION_TALK_8:
                            tirion->AI()->Talk(TIRION_FLASH_BACK_8);
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_TIRION_TALK_9:
                            tirion->AI()->Talk(TIRION_FLASH_BACK_9);
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_TIRION_TALK_10:
                            tirion->AI()->Talk(TIRION_FLASH_BACK_10);
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_TIRION_TALK_11:
                            tirion->AI()->Talk(TIRION_FLASH_BACK_11);
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_DARION_GET_UP:
                            me->RemoveAurasDueToSpell(SPELL_KNEEL);
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_DARION_TALK_6:
                            Talk(DARION_FLASH_BACK_6);
                            break;
                        case SCRIPT_PHASE_FLASH_BACK_TO_PHASE_EVENT_DONE:
                            progressEvent();
                            break;
                        case SCRIPT_PHASE_ANY_SET_WEATHER_TO_RAINING_REPEATING:
                        {
                            setZoneWeatherToRaining(true);
                            events.ScheduleEvent(SCRIPT_PHASE_ANY_SET_WEATHER_TO_RAINING_REPEATING, 2s);
                            break;
                        }
                        case SCRIPT_PHASE_ANY_RESPAWN:
                        {
                            me->DespawnOrUnsummon();
                            break;
                        }
                        default:
                            break;
                        }
                    }

                    break;
                    case PHASE_EVENT_DONE:
                        while (uint32 eventId = events.ExecuteEvent())
                        {
                            switch (eventId)
                            {
                            case SCRIPT_PHASE_ANY_RESPAWN:
                                me->DespawnOrUnsummon();
                                break;
                            default:
                                break;
                            }
                        }

                        break;
                default:
                    break;
                }
            }
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return new npc_highlord_darion_mograineAI(creature);
        }
};

enum MASTER_darion_summoned_unit
{
    //all npc stuff
    SCRIPT_SET_REACT_STATE_AGGRESSIVE = 1,
    SCRIPT_UPDATE_TARGET_LIST = 2,

    //npc spell cast scripts
    //flesh behemoth
    SCRIPT_FLESH_BEHEMOTH_CAST_STOMP = 3,
    SCRIPT_FLESH_BEHEMOTH_CONTINUE_AFTER_CAST_STOMP = 4,
    SCRIPT_FLESH_BEHEMOTH_CAST_THUNDERCLAP = 5,
    //rampaging abomination
    SCRIPT_RAMPAGING_ABOMINATION_CAST_CLEAVE = 6,
    SCRIPT_RAMPAGING_ABOMINATION_CAST_SCOURGE_HOOK = 7,
    SCRIPT_RAMPAGING_ABOINATION_CONTINUE_AFTER_SCOURGE_HOOK = 8,
    //warrior of the frozen wastes
    SCRIPT_WARRIOR_OF_THE_FROZEN_WASTES_CAST_CLEAVE = 9,
    //koltira, orbaz and thassarian
    SCRIPT_DK_CAST_PLAGUE_STRIKE = 10,
    //defender of the light
    SCRIPT_DEFENDER_OF_THE_LIGHT_CAST_HOLY_LIGHT = 11,
    SCRIPT_DEFENDER_OF_THE_LIGHT_CONTINUE_AFTER_HOLY_LIGHT = 12,
    SCRIPT_DEFENDER_OF_THE_LIGHT_CAST_HOLY_STRIKE = 13,
    SCRIPT_DEFENDER_OF_THE_LIGHT_CAST_UPPERCUT = 14,
    //korfax, champion of the light
    SCRIPT_KORFAX_CHAMPION_OF_THE_LIGHT_CAST_CLEAVE = 15,
    //commander eligor dawnbringer
    SCRIPT_COMMANDER_ELIGOR_DAWNBRINGER_CAST_HOLY_LIGHT = 16,
    SCRIPT_COMMANDER_ELIGOR_DAWNBRINGER_CONTINUE_AFTER_HOLY_LIGHT = 17,
    //rayne
    SCRIPT_RAYNE_CAST_REJUVENATION = 18,
    SCRIPT_RAYNE_CAST_STARFALL_SETUP = 19,
    SCRIPT_RAYNE_CAST_STARFALL = 20,
    SCRIPT_RAYNE_CONTINUE_AFTER_STARFALL = 21,
    SCRIPT_RAYNE_CAST_WRATH = 22,
    SCRIPT_RAYNE_CONTINUE_AFTER_WRATH = 23,
    //rimblat earthshatter
    SCRIPT_RIMBLAT_EARTHSHATTER_CAST_CHAIN_HEAL = 24,
    SCRIPT_RIMBLAT_EARTHSHATTER_CONTINUE_AFTER_CHAIN_HEAL = 25,
    SCRIPT_RIMBLAT_EARTHSHATTER_CAST_THUNDER = 26,
    //for final scene
    SCRIPT_HIT_BY_APOCALYPSE_SET_KNOCKDOWN = 27,

    //spell timers
    //flesh behemoth
    TIMER_FLESH_BEHEMOTH_STOMP_FIRST = 10,
    TIMER_FLESH_BEHEMOTH_STOMP_REPEAT = 10,
    TIMER_FLESH_BEHEMOTH_TUNDERCLAP_FIRST = 15,
    TIMER_FLESH_BEHEMOTH_TUNDERCLAP_REPEAT = 15,
    //rampaging abomination
    TIMER_RAMPAGING_ABOMINATION_CLEAVE_FIRST = 10,
    TIMER_RAMPAGING_ABOMINATION_CLEAVE_REPEAT = 10,
    TIMER_RAMPAGING_ABOMINATION_SCOURGE_HOOK_FIRST = 15,
    TIMER_RAMPAGING_ABOMINATION_SCOURGE_HOOK_REPEAT = 15,
    //warrior of the frozen wastes
    TIMER_WARRIOR_OF_THE_FROZEN_WASTES_CLEAVE_FIRST = 10,
    TIMER_WARRIOR_OF_THE_FROZEN_WASTES_CLEAVE_REPEAT = 10,
    //koltira, orbaz and thassarian
    TIMER_DK_PLAGUE_STRIKE_FIRST = 10,
    TIMER_DK_PLAGUE_STRIKE_REPEAT = 10,
    //defender of the light
    TIMER_DEFENDER_OF_THE_LIGHT_HOLY_LIGHT_FIRST = 10,
    TIMER_DEFENDER_OF_THE_LIGHT_HOLY_LIGHT_REPEAT = 10,
    TIMER_DEFENDER_OF_THE_LIGHT_HOLY_STRIKE_FIRST = 10,
    TIMER_DEFENDER_OF_THE_LIGHT_HOLY_STRIKE_REPEAT = 10,
    TIMER_DEFENDER_OF_THE_LIGHT_UPPERCUT_FIRST = 15,
    TIMER_DEFENDER_OF_THE_LIGHT_UPPERCUT_REPEAT = 15,
    //korfax, champion of the light
    TIMER_KORFAX_CHAMPION_OF_THE_LIGHT_CLEAVE_FIRST = 10,
    TIMER_KORFAX_CHAMPION_OF_THE_LIGHT_CLEAVE_REPEAT = 10,
    //commander eligor dawnbringer
    TIMER_COMMANDER_ELIGOR_DAWNBRINGER_HOLY_LIGHT_FIRST = 10,
    TIMER_COMMANDER_ELIGOR_DAWNBRINGER_HOLY_LIGHT_REPEAT = 10,
    //rayne
    TIMER_RAYNE_REJUVENATION_FIRST = 10,
    TIMER_RAYNE_REJUVENATION_REPEAT = 10,
    TIMER_RAYNE_STARFALL_FIRST = 20,
    TIMER_RAYNE_STARFALL_REPEAT = 20,
    TIMER_RAYNE_WRATH_FIRST = 5,
    TIMER_RAYNE_WRATH_REPEAT = 5,
    //rimblat earthshatter
    TIMER_RIMBLAT_EARTHSHATTER_CHAIN_HEAL_FIRST = 10,
    TIMER_RIMBLAT_EARTHSHATTER_CHAIN_HEAL_REPEAT = 10,
    TIMER_RIMBLAT_EARTHSHATTER_THUNDER_FIRST = 15,
    TIMER_RIMBLAT_EARTHSHATTER_THUNDER_REPEAT = 15
};

class npc_MASTER_darion_summoned_unit : public CreatureScript
{
public:
    npc_MASTER_darion_summoned_unit() : CreatureScript("npc_MASTER_darion_summoned_unit") { }

    struct npc_MASTER_darion_summoned_unitAI : public ScriptedAI
    {
        //##attributes##
        //creature's creature_template id
        uint32 entry;
        //timed event notifier
        EventMap events;
        //range at which the creature will aquire targets in
        float targetAquisitionRange;
        //holds all targets within targetAquisitionRange aquired through updateInCombatWithList()
        std::list<Unit*> targetList;
        //used to hold target info for scripts
        Unit *tempTarget1;
        //used to determine if the unit has been out of combat without re-entering combat
        bool first_outOfCombat_recent;
        //used to determine if the unit has been in combat without recently leaving combat
        bool first_inCombat_recent;
        //used to determine if the unit has entered combat at all
        bool first_inCombat_ever;
        //used to determine if the unit is casting
        bool casting;
        //bool used to enable one shot scripts on reaching invincibility hp
        bool invincibility_oneShot;

        npc_MASTER_darion_summoned_unitAI(Creature* creature) : ScriptedAI(creature)
        {
            entry = me->GetEntry();
            events = EventMap();
            targetAquisitionRange = COMBAT_TARGET_AQUISITION_RANGE;
            targetList = std::list<Unit*>();
            tempTarget1 = nullptr;
            first_outOfCombat_recent = true;
            first_inCombat_recent = true;
            first_inCombat_ever = true;
            casting = false;
            invincibility_oneShot = false;
            me->SetReactState(REACT_PASSIVE);
            //events.ScheduleEvent(SCRIPT_SET_REACT_STATE_AGGRESSIVE, 5s);
        }

        ~npc_MASTER_darion_summoned_unitAI(void) override
        {

        }

        //used by updateCombatList for creatures to shorten code
        void pushBackEligibleTargetsFromList(std::list<Creature*> &creatureList)
        {
            if (!creatureList.empty())
            {
                std::list<Creature*>::iterator cItr;
                Creature *cItrTarget = nullptr;

                for (cItr = creatureList.begin(); cItr != creatureList.end(); ++cItr)
                {
                    cItrTarget = (*cItr);
                    if ((cItrTarget->GetReactState() == REACT_AGGRESSIVE) && cItrTarget->IsAlive() && cItrTarget->IsInWorld())
                    {
                        //me->Say("Creature target found.", LANG_UNIVERSAL);
                        targetList.push_back(cItrTarget->ToUnit());
                    }
                }
            }
        }

        //used by updateCombatList for players to shorten code
        void pushBackEligibleTargetsFromList(std::list<Player*> &playerList)
        {
            if (!playerList.empty())
            {
                //me->Say("Player target found.", LANG_UNIVERSAL);
                std::list<Player*>::iterator pItr;
                Player *pItrTarget = nullptr;

                for (pItr = playerList.begin(); pItr != playerList.end(); ++pItr)
                {
                    pItrTarget = (*pItr);

                    if (me->IsHostileTo(pItrTarget) && pItrTarget->IsAlive() && pItrTarget->IsInWorld())
                    {
                        //me->Say("Player target found.", LANG_UNIVERSAL);
                        targetList.push_back(pItrTarget->ToUnit());
                    }
                }
            }
        }

        //gets all creatures of the proper ids for their corresponding faction (scourge or dawn)
        //within targetAquisitionRange and then adds them to targetList and sets the creature in combat with all of them
        void updateInCombatWithList(void)
        {
            //me->Say("updateInCombatWithList() called.", LANG_UNIVERSAL);
            targetList.clear();

            if ((entry == ID_FLESH_BEHEMOTH) || (entry == ID_RAMPAGING_ABOMINATION) || (entry == ID_WARRIOR_OF_THE_FROZEN_WASTES) || (entry == ID_VOLATILE_GHOUL) || (entry == ID_HIGHLORD_DARION_MOGRAINE) || (entry == ID_KOLTIRA_DEATHWEAVER) || (entry == ID_ORBAZ_BLOODBANE) || (entry == ID_THASSARIAN))
            {
                //define individual target lists
                std::list<Creature*> defenderOfTheLightList = std::list<Creature*>();
                std::list<Creature*> maxwellList = std::list<Creature*>();
                std::list<Creature*> korfaxList = std::list<Creature*>();
                std::list<Creature*> leonidList = std::list<Creature*>();
                std::list<Creature*> nicholasList = std::list<Creature*>();
                std::list<Creature*> eligorList = std::list<Creature*>();
                std::list<Creature*> rayneList = std::list<Creature*>();
                std::list<Creature*> rimblatList = std::list<Creature*>();

                //populate individual target lists
                me->GetCreatureListWithEntryInGrid(defenderOfTheLightList, ID_DEFENDER_OF_THE_LIGHT, targetAquisitionRange);
                me->GetCreatureListWithEntryInGrid(maxwellList, ID_LORD_MAXWELL_TYROSUS, targetAquisitionRange);
                me->GetCreatureListWithEntryInGrid(korfaxList, ID_KORFAX_CHAMPION_OF_THE_LIGHT, targetAquisitionRange);
                me->GetCreatureListWithEntryInGrid(leonidList, ID_LEONID_BARTHALOMEW_THE_REVERED, targetAquisitionRange);
                me->GetCreatureListWithEntryInGrid(nicholasList, ID_DUKE_NICHOLAS_ZVERENHOFF, targetAquisitionRange);
                me->GetCreatureListWithEntryInGrid(eligorList, ID_COMMANDER_ELIGOR_DAWNBRINGER, targetAquisitionRange);
                me->GetCreatureListWithEntryInGrid(rayneList, ID_RAYNE, targetAquisitionRange);
                me->GetCreatureListWithEntryInGrid(rimblatList, ID_RIMBLAT_EARTHSHATTER, targetAquisitionRange);

                //combine all target lists into targetList based on eligible for combat criteria
                pushBackEligibleTargetsFromList(defenderOfTheLightList);
                pushBackEligibleTargetsFromList(maxwellList);
                pushBackEligibleTargetsFromList(korfaxList);
                pushBackEligibleTargetsFromList(leonidList);
                pushBackEligibleTargetsFromList(nicholasList);
                pushBackEligibleTargetsFromList(eligorList);
                pushBackEligibleTargetsFromList(rayneList);
                pushBackEligibleTargetsFromList(rimblatList);
            }
            else if ((entry == ID_DEFENDER_OF_THE_LIGHT) || (entry == ID_LORD_MAXWELL_TYROSUS) || (entry == ID_KORFAX_CHAMPION_OF_THE_LIGHT) || (entry == ID_LEONID_BARTHALOMEW_THE_REVERED) || (entry == ID_DUKE_NICHOLAS_ZVERENHOFF) || (entry == ID_COMMANDER_ELIGOR_DAWNBRINGER) || (entry == ID_RAYNE) || (entry == ID_RIMBLAT_EARTHSHATTER))
            {
                //define individual target lists
                std::list<Creature*> fleshBehemothList = std::list<Creature*>();
                std::list<Creature*> rampagingAbominationList = std::list<Creature*>();
                std::list<Creature*> warriorOfTheFrozenWastesList = std::list<Creature*>();
                std::list<Creature*> volatileGhoulList = std::list<Creature*>();
                std::list<Creature*> darionList = std::list<Creature*>();
                std::list<Creature*> koltiraList = std::list<Creature*>();
                std::list<Creature*> orbazList = std::list<Creature*>();
                std::list<Creature*> thassarianList = std::list<Creature*>();

                //populate individual target lists
                me->GetCreatureListWithEntryInGrid(fleshBehemothList, ID_FLESH_BEHEMOTH, targetAquisitionRange);
                me->GetCreatureListWithEntryInGrid(rampagingAbominationList, ID_RAMPAGING_ABOMINATION, targetAquisitionRange);
                me->GetCreatureListWithEntryInGrid(warriorOfTheFrozenWastesList, ID_WARRIOR_OF_THE_FROZEN_WASTES, targetAquisitionRange);
                me->GetCreatureListWithEntryInGrid(volatileGhoulList, ID_VOLATILE_GHOUL, targetAquisitionRange);
                me->GetCreatureListWithEntryInGrid(darionList, ID_HIGHLORD_DARION_MOGRAINE, targetAquisitionRange);
                me->GetCreatureListWithEntryInGrid(koltiraList, ID_KOLTIRA_DEATHWEAVER, targetAquisitionRange);
                me->GetCreatureListWithEntryInGrid(orbazList, ID_ORBAZ_BLOODBANE, targetAquisitionRange);
                me->GetCreatureListWithEntryInGrid(thassarianList, ID_THASSARIAN, targetAquisitionRange);

                //combine all target lists into targetList based on eligible for combat criteria
                pushBackEligibleTargetsFromList(fleshBehemothList);
                pushBackEligibleTargetsFromList(rampagingAbominationList);
                pushBackEligibleTargetsFromList(warriorOfTheFrozenWastesList);
                pushBackEligibleTargetsFromList(volatileGhoulList);
                pushBackEligibleTargetsFromList(darionList);
                pushBackEligibleTargetsFromList(koltiraList);
                pushBackEligibleTargetsFromList(orbazList);
                pushBackEligibleTargetsFromList(thassarianList);
            }

            //handle hostile players
            std::list<Player*> hostilePlayerList = std::list<Player*>();
            me->GetPlayerListInGrid(hostilePlayerList, targetAquisitionRange);
            pushBackEligibleTargetsFromList(hostilePlayerList);

            //set creature in combat with all targets
            if (!targetList.empty())
            {
                for (std::list<Unit*>::iterator itr = targetList.begin(); itr != targetList.end(); ++itr)
                {
                    //me->Say("Set in combat with target.", LANG_UNIVERSAL);
                    me->GetCombatManager().SetInCombatWith(*itr);
                }
            }
        }

        //handles the death of a volatile ghoul
        void volatileGhoul_explosionOnDeath(void)
        {
            events.Reset();
            me->SetReactState(REACT_PASSIVE);
            me->GetMotionMaster()->Clear();
            me->CastSpell(me, SPELL_GHOULSPLOSION);
            me->KillSelf();
            invincibility_oneShot = true;
        }

        //handles the stomp cast for a flesh behemoth
        void fleshBehemoth_cast_stomp(void)
        {
            tempTarget1 = me->GetVictim();
            me->GetMotionMaster()->Clear();
            me->GetMotionMaster()->MoveIdle();
            me->CastSpell(me, SPELL_STOMP);
            casting = true;
            events.ScheduleEvent(SCRIPT_FLESH_BEHEMOTH_CONTINUE_AFTER_CAST_STOMP, 1s);
        }

        void fleshBehemoth_cast_thunderClap(void)
        {
            if (me->IsWithinMeleeRange(me->GetVictim()) && !casting)
            {
                me->CastSpell(me, SPELL_THUNDERCLAP);
                events.ScheduleEvent(SCRIPT_FLESH_BEHEMOTH_CAST_THUNDERCLAP, (TIMER_FLESH_BEHEMOTH_TUNDERCLAP_REPEAT * 1s));
            }
            else
            {
                //me->Say("out of range for thunderclap, rescheduling by 1s", LANG_UNIVERSAL);
                events.ScheduleEvent(SCRIPT_FLESH_BEHEMOTH_CAST_THUNDERCLAP, 1s);
            }
        }

        //cleans up the stomp cast for a flash behemoth
        void fleshBehemoth_continueAfterStomp(void)
        {
            casting = false;
            me->GetMotionMaster()->MoveChase(tempTarget1);
            tempTarget1 = nullptr;
            events.ScheduleEvent(SCRIPT_FLESH_BEHEMOTH_CAST_STOMP, (TIMER_FLESH_BEHEMOTH_STOMP_REPEAT * 1s));
        }

        //handles the cleave cast for a rampaging abomination
        void rampagingAbomination_cast_cleave(void)
        {
            if (me->IsWithinMeleeRange(me->GetVictim()) && !casting)
            {
                me->CastSpell(me->GetVictim(), SPELL_CLEAVE);
                events.ScheduleEvent(SCRIPT_RAMPAGING_ABOMINATION_CAST_CLEAVE, (TIMER_RAMPAGING_ABOMINATION_CLEAVE_REPEAT * 1s));
            }
            else
            {
                //me->Say("out of range for cleave, rescheduling by 1s", LANG_UNIVERSAL);
                events.ScheduleEvent(SCRIPT_RAMPAGING_ABOMINATION_CAST_CLEAVE, 1s);
            }
        }

        //handles the scourge hook cast for a rampaging abomination
        void rampagingAbomination_cast_scourge_hook(void)
        {
            float distanceToTarget = me->GetDistance(me->GetVictim());

            if ((distanceToTarget >= 8) && (distanceToTarget <= 40))
            {
                tempTarget1 = me->GetVictim();
                me->GetMotionMaster()->Clear();
                me->GetMotionMaster()->MoveIdle();
                me->CastSpell(me->GetVictim(), SPELL_SCOURGE_HOOK);
                casting = true;
                events.ScheduleEvent(SCRIPT_RAMPAGING_ABOINATION_CONTINUE_AFTER_SCOURGE_HOOK, 1s);
            }
            else
            {
                //me->Say("out of proper range for scourge hook, rescheduling by 1s", LANG_UNIVERSAL);
                events.ScheduleEvent(SCRIPT_RAMPAGING_ABOMINATION_CAST_SCOURGE_HOOK, 1s);
            }
        }

        //cleans up the scourge hook cast for a rampaging abomination
        void rampagingAbomination_continueAfterScourgeHook(void)
        {
            casting = false;
            me->GetMotionMaster()->MoveChase(me->GetVictim());
            tempTarget1 = nullptr;
            events.ScheduleEvent(SCRIPT_RAMPAGING_ABOMINATION_CAST_SCOURGE_HOOK, (TIMER_RAMPAGING_ABOMINATION_SCOURGE_HOOK_REPEAT * 1s));
        }

        //handles the cleave cast for a warrior of the frozen wastes
        void warriorOfTheFrozenWastes_cast_cleave(void)
        {
            if (me->IsWithinMeleeRange(me->GetVictim()))
            {
                me->CastSpell(me->GetVictim(), SPELL_CLEAVE);
                events.ScheduleEvent(SCRIPT_WARRIOR_OF_THE_FROZEN_WASTES_CAST_CLEAVE, (TIMER_WARRIOR_OF_THE_FROZEN_WASTES_CLEAVE_REPEAT * 1s));
            }
            else
            {
                //me->Say("out of range for cleave, rescheduling by 1s", LANG_UNIVERSAL);
                events.ScheduleEvent(SCRIPT_WARRIOR_OF_THE_FROZEN_WASTES_CAST_CLEAVE, 1s);
            }
        }

        void dk_cast_plague_strike(void)
        {
            if (me->IsWithinMeleeRange(me->GetVictim()))
            {
                me->CastSpell(me->GetVictim(), SPELL_PLAGUE_STRIKE);
                events.ScheduleEvent(SCRIPT_DK_CAST_PLAGUE_STRIKE, (TIMER_DK_PLAGUE_STRIKE_REPEAT * 1s));
            }
            else
            {
                //me->Say("out of range for plague strike, rescheduling by 1s", LANG_UNIVERSAL);
                events.ScheduleEvent(SCRIPT_DK_CAST_PLAGUE_STRIKE, 1s);
            }
        }

        void defenderOfTheLight_cast_holyLight(void)
        {
            tempTarget1 = me->GetVictim();
            me->GetMotionMaster()->Clear();
            me->GetMotionMaster()->MoveIdle();
            me->CastSpell(DoSelectLowestHpFriendly(40), SPELL_HOLY_LIGHT_DEFENDER);
            casting = true;
            events.ScheduleEvent(SCRIPT_DEFENDER_OF_THE_LIGHT_CONTINUE_AFTER_HOLY_LIGHT, 2500ms);
        }

        void defenderOfTheLight_continueAfterHolyLight(void)
        {
            casting = false;
            me->GetMotionMaster()->MoveChase(me->GetVictim());
            tempTarget1 = nullptr;
            events.ScheduleEvent(SCRIPT_DEFENDER_OF_THE_LIGHT_CAST_HOLY_LIGHT, (TIMER_DEFENDER_OF_THE_LIGHT_HOLY_LIGHT_REPEAT * 1s));
        }

        void defenderOfTheLight_cast_holyStrike(void)
        {
            if (me->IsWithinMeleeRange(me->GetVictim()) && !casting)
            {
                me->CastSpell(me->GetVictim(), SPELL_HOLY_STRIKE);
                events.ScheduleEvent(SCRIPT_DEFENDER_OF_THE_LIGHT_CAST_HOLY_STRIKE, (TIMER_DEFENDER_OF_THE_LIGHT_HOLY_STRIKE_REPEAT * 1s));
            }
            else
            {
                //me->Say("out of range for holy strike, rescheduling by 1s", LANG_UNIVERSAL);
                events.ScheduleEvent(SCRIPT_DEFENDER_OF_THE_LIGHT_CAST_HOLY_STRIKE, 1s);
            }
        }

        void defenderOfTheLight_cast_uppercut(void)
        {
            float distanceToTarget = me->GetDistance(me->GetVictim());

            if ((distanceToTarget >= 0) && (distanceToTarget <= 10) && !casting)
            {
                me->CastSpell(me->GetVictim(), SPELL_UPPERCUT);
                events.ScheduleEvent(SCRIPT_DEFENDER_OF_THE_LIGHT_CAST_UPPERCUT, (TIMER_DEFENDER_OF_THE_LIGHT_UPPERCUT_REPEAT * 1s));
            }
            else
            {
                //me->Say("out of proper range for uppercut, rescheduling by 1s", LANG_UNIVERSAL);
                events.ScheduleEvent(SCRIPT_DEFENDER_OF_THE_LIGHT_CAST_UPPERCUT, 1s);
            }
        }

        void korfaxChampionOfTheLight_cast_cleave(void)
        {
            if (me->IsWithinMeleeRange(me->GetVictim()))
            {
                me->CastSpell(me->GetVictim(), SPELL_CLEAVE);
                events.ScheduleEvent(SCRIPT_KORFAX_CHAMPION_OF_THE_LIGHT_CAST_CLEAVE, (TIMER_KORFAX_CHAMPION_OF_THE_LIGHT_CLEAVE_REPEAT * 1s));
            }
            else
            {
                //me->Say("out of range for cleave, rescheduling by 1s", LANG_UNIVERSAL);
                events.ScheduleEvent(SCRIPT_KORFAX_CHAMPION_OF_THE_LIGHT_CAST_CLEAVE, 1s);
            }
        }

        void commanderEligorDawnbringer_cast_holyLight(void)
        {
            tempTarget1 = me->GetVictim();
            me->GetMotionMaster()->Clear();
            me->GetMotionMaster()->MoveIdle();
            me->CastSpell(DoSelectLowestHpFriendly(40), SPELL_HOLY_LIGHT_ELIGOR);
            events.ScheduleEvent(SCRIPT_COMMANDER_ELIGOR_DAWNBRINGER_CONTINUE_AFTER_HOLY_LIGHT, 2500ms);
        }

        void commanderEligorDawnbringer_continueAfterHolyLight(void)
        {
            me->GetMotionMaster()->MoveChase(me->GetVictim());
            tempTarget1 = nullptr;
            events.ScheduleEvent(SCRIPT_COMMANDER_ELIGOR_DAWNBRINGER_CAST_HOLY_LIGHT, (TIMER_COMMANDER_ELIGOR_DAWNBRINGER_HOLY_LIGHT_REPEAT * 1s));
        }

        void rayne_cast_rejuvenation(void)
        {
            if (!casting)
            {
                me->CastSpell(DoSelectLowestHpFriendly(40), SPELL_REJUVENATION);
                events.ScheduleEvent(SCRIPT_RAYNE_CAST_REJUVENATION, (TIMER_RAYNE_REJUVENATION_REPEAT * 1s));
            }
            else
            {
                //me->Say("out of range for rejuventation, rescheduling by 1s", LANG_UNIVERSAL);
                events.ScheduleEvent(SCRIPT_RAYNE_CAST_REJUVENATION, 1s);
            }
        }

        void rayne_cast_starfall_setup(void)
        {
            float distanceToTarget = me->GetDistance(me->GetVictim());

            if ((distanceToTarget >= 0) && (distanceToTarget <= 30) && !casting)
            {
                tempTarget1 = me->GetVictim();
                me->GetMotionMaster()->Clear();
                me->GetMotionMaster()->MoveIdle();
                events.ScheduleEvent(SCRIPT_RAYNE_CAST_STARFALL, 500ms);
                casting = true;
            }
            else
            {
                //me->Say("out of proper range for starfall, rescheduling by 1s", LANG_UNIVERSAL);
                events.ScheduleEvent(SCRIPT_RAYNE_CAST_STARFALL_SETUP, 1s);
            }
        }

        void rayne_cast_starfall(void)
        {
            me->CastSpell(me->GetVictim()->GetPosition(), SPELL_STARFALL);
            events.ScheduleEvent(SCRIPT_RAYNE_CONTINUE_AFTER_STARFALL, 10s);
        }

        void rayne_continueAfterStarfall(void)
        {
            casting = false;
            me->GetMotionMaster()->MoveChase(me->GetVictim());
            tempTarget1 = nullptr;
            events.ScheduleEvent(SCRIPT_RAYNE_CAST_STARFALL_SETUP, (TIMER_RAYNE_STARFALL_REPEAT * 1s));
        }

        void rayne_cast_wrath(void)
        {
            float distanceToTarget = me->GetDistance(me->GetVictim());

            if ((distanceToTarget >= 0) && (distanceToTarget <= 40) && !casting)
            {
                tempTarget1 = me->GetVictim();
                me->GetMotionMaster()->Clear();
                me->GetMotionMaster()->MoveIdle();
                me->CastSpell(me->GetVictim(), SPELL_WRATH);
                casting = true;
                events.ScheduleEvent(SCRIPT_RAYNE_CONTINUE_AFTER_WRATH, 2s);
            }
            else
            {
                //me->Say("out of proper range for wrath, rescheduling by 1s", LANG_UNIVERSAL);
                events.ScheduleEvent(SCRIPT_RAYNE_CAST_WRATH, 1s);
            }
        }

        void rayne_continueAfterWrath(void)
        {
            casting = false;
            me->GetMotionMaster()->MoveChase(me->GetVictim());
            tempTarget1 = nullptr;
            events.ScheduleEvent(SCRIPT_RAYNE_CAST_WRATH, (TIMER_RAYNE_WRATH_REPEAT * 1s));
        }

        void rimblatEarthshatter_cast_chainHeal(void)
        {
            tempTarget1 = me->GetVictim();
            me->GetMotionMaster()->Clear();
            me->GetMotionMaster()->MoveIdle();
            me->CastSpell(DoSelectLowestHpFriendly(40), SPELL_CHAIN_HEAL);
            casting = true;
            events.ScheduleEvent(SCRIPT_RIMBLAT_EARTHSHATTER_CONTINUE_AFTER_CHAIN_HEAL, 2500ms);
        }

        void rimblatEarthshatter_continueAfterChainHeal(void)
        {
            casting = false;
            me->GetMotionMaster()->MoveChase(me->GetVictim());
            tempTarget1 = nullptr;
            events.ScheduleEvent(SCRIPT_RIMBLAT_EARTHSHATTER_CAST_CHAIN_HEAL, (TIMER_RIMBLAT_EARTHSHATTER_CHAIN_HEAL_REPEAT * 1s));
        }

        void rimblatEarthshatter_cast_thunder(void)
        {
            if (me->IsWithinMeleeRange(me->GetVictim()) && !casting)
            {
                me->CastSpell(me, SPELL_THUNDER);
                events.ScheduleEvent(SCRIPT_RIMBLAT_EARTHSHATTER_CAST_THUNDER, (TIMER_RIMBLAT_EARTHSHATTER_THUNDER_REPEAT * 1s));
            }
            else
            {
                //me->Say("out of range for thunder, rescheduling by 1s", LANG_UNIVERSAL);
                events.ScheduleEvent(SCRIPT_RIMBLAT_EARTHSHATTER_CAST_THUNDER, 1s);
            }
        }

        void SpellHit(Unit* caster, SpellInfo const* spellInfo) override
        {
            if (spellInfo->Id == SPELL_APOCALYPSE)
            {
                events.ScheduleEvent(SCRIPT_HIT_BY_APOCALYPSE_SET_KNOCKDOWN, 1500ms);
            }
        }

        void specialDawnNPCs_scriptOnInvincibilityHp(void)
        {
            me->SetReactState(REACT_PASSIVE);
            me->GetCombatManager().EndAllCombat();
            me->GetMotionMaster()->Clear();
            me->GetMotionMaster()->MoveIdle();
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_SILENCED | UNIT_FLAG_PACIFIED | UNIT_FLAG_NOT_SELECTABLE);
            Talk(SPECIAL_DAWN_NPC_DEFEATED);
            me->CastSpell(me, SPELL_FEIGN_DEATH);
            invincibility_oneShot = true;
        }

        // Called at waypoint reached or point movement finished
        void MovementInform(uint32 type, uint32 id) override
        {
            //me->Say("point movement finished.", LANG_UNIVERSAL);
            switch (entry)
            {
            case ID_HIGHLORD_TIRION_FORDRING:
                if (type == POINT_MOTION_TYPE && id == 0)
                {
                    me->Dismount();
                    me->GetMotionMaster()->Clear();
                    me->GetMotionMaster()->MoveIdle();
                    me->SetFacingTo(highlord_tirion_fordring_to_lights_hope.GetOrientation(), true);
                }
                else if (id == 2)
                {
                    me->SetFacingTo(tirion_to_darion_to_heal.GetOrientation(), true);
                }
                else if (id == 3)
                {
                    me->SetFacingTo(tirion_to_speech_position.GetOrientation(), true);
                }

                break;
            case ID_LORD_MAXWELL_TYROSUS:
                if (id == 1)
                {
                    me->GetMotionMaster()->Clear();
                    me->GetMotionMaster()->MoveIdle();
                    me->SetFacingTo(maxwell_to_lights_hope_battle_lost.GetOrientation(), true);
                }
                else if (id == 2)
                {
                    me->SetFacingTo(maxwell_final_position.GetOrientation(), true);
                }

                break;
            case ID_KORFAX_CHAMPION_OF_THE_LIGHT:
                if (id == 1)
                {
                    me->GetMotionMaster()->Clear();
                    me->GetMotionMaster()->MoveIdle();
                    me->SetFacingTo(korfax_to_lights_hope_battle_lost.GetOrientation(), true);
                }
                else if (id == 2)
                {
                    me->SetFacingTo(korfax_final_position.GetOrientation(), true);
                }

                break;
            case ID_LEONID_BARTHALOMEW_THE_REVERED:
                if (id == 1)
                {
                    me->GetMotionMaster()->Clear();
                    me->GetMotionMaster()->MoveIdle();
                    me->SetFacingTo(leonid_to_lights_hope_battle_lost.GetOrientation(), true);
                }
                else if (id == 2)
                {
                    me->SetFacingTo(leonid_final_position.GetOrientation(), true);
                }

                break;
            case ID_DUKE_NICHOLAS_ZVERENHOFF:
                if (id == 1)
                {
                    me->GetMotionMaster()->Clear();
                    me->GetMotionMaster()->MoveIdle();
                    me->SetFacingTo(nicholas_to_lights_hope_battle_lost.GetOrientation(), true);
                }
                else if (id == 2)
                {
                    me->SetFacingTo(nicholas_final_position.GetOrientation(), true);
                }

                break;
            case ID_COMMANDER_ELIGOR_DAWNBRINGER:
                if (id == 1)
                {
                    me->GetMotionMaster()->Clear();
                    me->GetMotionMaster()->MoveIdle();
                    me->SetFacingTo(eligor_to_lights_hope_battle_lost.GetOrientation(), true);
                }
                else if (id == 2)
                {
                    me->SetFacingTo(eligor_final_position.GetOrientation(), true);
                }

                break;
            case ID_RAYNE:
                if (id == 1)
                {
                    me->GetMotionMaster()->Clear();
                    me->GetMotionMaster()->MoveIdle();
                    me->SetFacingTo(rayne_to_lights_hope_battle_lost.GetOrientation(), true);
                }
                else if (id == 2)
                {
                    me->SetFacingTo(rayne_final_position.GetOrientation(), true);
                }

                break;
            case ID_RIMBLAT_EARTHSHATTER:
                if (id == 1)
                {
                    me->GetMotionMaster()->Clear();
                    me->GetMotionMaster()->MoveIdle();
                    me->SetFacingTo(rimblat_to_lights_hope_battle_lost.GetOrientation(), true);
                }
                else if (id == 2)
                {
                    me->SetFacingTo(rimblat_final_position.GetOrientation(), true);
                }

                break;
            case ID_DEFENDER_OF_THE_LIGHT:
                if (id >= 1 && id <= 21)
                {
                    me->GetMotionMaster()->Clear();
                    me->GetMotionMaster()->MoveIdle();
                    me->SetFacingTo(defender_of_the_light_to_lights_hope_battle_lost[(id - 1)].GetOrientation(), true);
                    me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_READY2H);
                    me->HandleEmoteCommand(EMOTE_STATE_READY2H);
                }

                break;
            case ID_KOLTIRA_DEATHWEAVER:
                if (id == 1)
                {
                    me->GetMotionMaster()->Clear();
                    me->GetMotionMaster()->MoveIdle();
                    me->GetMotionMaster()->MovePoint(2, koltira_to_lights_hope_battle_lost.GetPositionX(), koltira_to_lights_hope_battle_lost.GetPositionY(), (koltira_to_lights_hope_battle_lost.GetPositionZ() + 10.0f));
                }
                else if (id == 2)
                {
                    me->GetMotionMaster()->Clear();
                    me->GetMotionMaster()->MoveIdle();
                    me->SetWalk(false);
                    me->SetCanFly(false);
                    me->SetDisableGravity(false);
                    me->RemoveUnitMovementFlag(MOVEMENTFLAG_FLYING);
                    me->RemoveAurasDueToSpell(SPELL_LIGHT_OF_DAWN_PRISON);
                    me->GetMotionMaster()->MoveFall();
                    me->SetFacingTo(koltira_to_lights_hope_battle_lost.GetOrientation(), true);
                    me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_READY2H);
                    me->HandleEmoteCommand(EMOTE_STATE_READY2H);
                }

                break;
            case ID_THASSARIAN:
                if (id == 1)
                {
                    me->GetMotionMaster()->Clear();
                    me->GetMotionMaster()->MoveIdle();
                    me->GetMotionMaster()->MovePoint(2, thassarian_to_lights_hope_battle_lost.GetPositionX(), thassarian_to_lights_hope_battle_lost.GetPositionY(), (thassarian_to_lights_hope_battle_lost.GetPositionZ() + 10.0f));
                }
                else if (id == 2)
                {
                    me->GetMotionMaster()->Clear();
                    me->GetMotionMaster()->MoveIdle();
                    me->SetWalk(false);
                    me->SetCanFly(false);
                    me->SetDisableGravity(false);
                    me->RemoveUnitMovementFlag(MOVEMENTFLAG_FLYING);
                    me->RemoveAurasDueToSpell(SPELL_LIGHT_OF_DAWN_PRISON);
                    me->GetMotionMaster()->MoveFall();
                    me->SetFacingTo(thassarian_to_lights_hope_battle_lost.GetOrientation(), true);
                    me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_READY2H);
                    me->HandleEmoteCommand(EMOTE_STATE_READY2H);
                }

                break;
            default:
                break;
            }
        }

        //used to handle npcs that have an invincibility hp value
        void DamageTaken(Unit* attacker, uint32& damage) override
        {
            switch (entry)
            {
            case ID_VOLATILE_GHOUL:
            case ID_KOLTIRA_DEATHWEAVER:
            case ID_ORBAZ_BLOODBANE:
            case ID_THASSARIAN:
            case ID_LORD_MAXWELL_TYROSUS:
            case ID_KORFAX_CHAMPION_OF_THE_LIGHT:
            case ID_LEONID_BARTHALOMEW_THE_REVERED:
            case ID_DUKE_NICHOLAS_ZVERENHOFF:
            case ID_COMMANDER_ELIGOR_DAWNBRINGER:
            case ID_RAYNE:
            case ID_RIMBLAT_EARTHSHATTER:
                if ((me->GetHealth() - damage) <= INVINCIBILITY_HP)
                {
                    damage = me->GetHealth() - INVINCIBILITY_HP;
                }

                if (damage >= me->GetHealth() - INVINCIBILITY_HP)
                {
                    damage = 0;
                    me->SetHealth(INVINCIBILITY_HP);
                }
                break;
            default:
                break;
            }
        }

        void Reset() override
        {
            
        }

        void JustDied(Unit* killer) override
        {
            events.Reset();
            me->GetMotionMaster()->Clear();
            me->GetMotionMaster()->MoveIdle();
        }

        void UpdateAI(uint32 diff) override
        {
            if (entry != ID_THE_LICH_KING)
            {
                if (!events.Empty())
                {
                    events.Update(diff);
                }

                //for npcs that need to do things at the invincibility hp level
                if (me->GetHealth() == INVINCIBILITY_HP && !invincibility_oneShot)
                {
                    switch (entry)
                    {
                    case ID_VOLATILE_GHOUL:
                        volatileGhoul_explosionOnDeath();
                        break;
                    case ID_KOLTIRA_DEATHWEAVER:
                    case ID_ORBAZ_BLOODBANE:
                    case ID_THASSARIAN:
                        me->SetHealth(me->GetMaxHealth());
                        break;
                    case ID_LORD_MAXWELL_TYROSUS:
                    case ID_KORFAX_CHAMPION_OF_THE_LIGHT:
                    case ID_LEONID_BARTHALOMEW_THE_REVERED:
                    case ID_DUKE_NICHOLAS_ZVERENHOFF:
                    case ID_COMMANDER_ELIGOR_DAWNBRINGER:
                    case ID_RAYNE:
                    case ID_RIMBLAT_EARTHSHATTER:
                        specialDawnNPCs_scriptOnInvincibilityHp();
                        break;
                    default:
                        break;
                    }
                }

                if (me->GetReactState() == REACT_AGGRESSIVE)
                {
                    //if the unit is already in combat and has a target that they are attacking
                    if (me->IsInCombat() && me->GetVictim())
                    {
                        //potential fix for combat crashing that's been happeneing
                        if (!(me->GetVictim()->IsAlive()) || !(me->GetVictim()->IsInWorld()))
                        {
                            updateInCombatWithList();
                            Unit *target = me->GetCombatManager().GetAnyTarget();
                            me->GetMotionMaster()->MoveChase(target);
                            me->Attack(target, true);

                            if (casting)
                            {
                                tempTarget1 = target;
                            }
                        }

                        //used for initiation of spell cast scripts 
                        if (first_inCombat_ever)
                        {
                            switch (entry)
                            {
                            case ID_FLESH_BEHEMOTH:
                                events.ScheduleEvent(SCRIPT_FLESH_BEHEMOTH_CAST_STOMP, (TIMER_FLESH_BEHEMOTH_STOMP_FIRST * 1s));
                                events.ScheduleEvent(SCRIPT_FLESH_BEHEMOTH_CAST_THUNDERCLAP, (TIMER_FLESH_BEHEMOTH_TUNDERCLAP_FIRST * 1s));
                                break;
                            case ID_RAMPAGING_ABOMINATION:
                                events.ScheduleEvent(SCRIPT_RAMPAGING_ABOMINATION_CAST_CLEAVE, (TIMER_RAMPAGING_ABOMINATION_CLEAVE_FIRST * 1s));
                                events.ScheduleEvent(SCRIPT_RAMPAGING_ABOMINATION_CAST_SCOURGE_HOOK, (TIMER_RAMPAGING_ABOMINATION_SCOURGE_HOOK_FIRST * 1s));
                                break;
                            case ID_WARRIOR_OF_THE_FROZEN_WASTES:
                                events.ScheduleEvent(SCRIPT_WARRIOR_OF_THE_FROZEN_WASTES_CAST_CLEAVE, (TIMER_WARRIOR_OF_THE_FROZEN_WASTES_CLEAVE_FIRST * 1s));
                                break;
                            case ID_KOLTIRA_DEATHWEAVER:
                            case ID_ORBAZ_BLOODBANE:
                            case ID_THASSARIAN:
                                events.ScheduleEvent(SCRIPT_DK_CAST_PLAGUE_STRIKE, (TIMER_DK_PLAGUE_STRIKE_FIRST * 1s));
                                break;
                            case ID_DEFENDER_OF_THE_LIGHT:
                                events.ScheduleEvent(SCRIPT_DEFENDER_OF_THE_LIGHT_CAST_HOLY_LIGHT, (TIMER_DEFENDER_OF_THE_LIGHT_HOLY_LIGHT_FIRST * 1s));
                                events.ScheduleEvent(SCRIPT_DEFENDER_OF_THE_LIGHT_CAST_HOLY_STRIKE, (TIMER_DEFENDER_OF_THE_LIGHT_HOLY_STRIKE_FIRST * 1s));
                                events.ScheduleEvent(SCRIPT_DEFENDER_OF_THE_LIGHT_CAST_UPPERCUT, (TIMER_DEFENDER_OF_THE_LIGHT_UPPERCUT_FIRST * 1s));
                                break;
                            case ID_KORFAX_CHAMPION_OF_THE_LIGHT:
                                events.ScheduleEvent(SCRIPT_KORFAX_CHAMPION_OF_THE_LIGHT_CAST_CLEAVE, (TIMER_KORFAX_CHAMPION_OF_THE_LIGHT_CLEAVE_FIRST * 1s));
                                break;
                            case ID_COMMANDER_ELIGOR_DAWNBRINGER:
                                events.ScheduleEvent(SCRIPT_COMMANDER_ELIGOR_DAWNBRINGER_CAST_HOLY_LIGHT, (TIMER_COMMANDER_ELIGOR_DAWNBRINGER_HOLY_LIGHT_FIRST * 1s));
                                break;
                            case ID_RAYNE:
                                events.ScheduleEvent(SCRIPT_RAYNE_CAST_REJUVENATION, (TIMER_RAYNE_REJUVENATION_FIRST * 1s));
                                events.ScheduleEvent(SCRIPT_RAYNE_CAST_STARFALL_SETUP, (TIMER_RAYNE_STARFALL_FIRST * 1s));
                                events.ScheduleEvent(SCRIPT_RAYNE_CAST_WRATH, (TIMER_RAYNE_WRATH_FIRST * 1s));
                                break;
                            case ID_RIMBLAT_EARTHSHATTER:
                                events.ScheduleEvent(SCRIPT_RIMBLAT_EARTHSHATTER_CAST_CHAIN_HEAL, (TIMER_RIMBLAT_EARTHSHATTER_CHAIN_HEAL_FIRST * 1s));
                                events.ScheduleEvent(SCRIPT_RIMBLAT_EARTHSHATTER_CAST_THUNDER, (TIMER_RIMBLAT_EARTHSHATTER_THUNDER_FIRST * 1s));
                                break;
                            default:
                                break;
                            }

                            first_inCombat_ever = false;
                        }

                        if (first_inCombat_recent)
                        {
                            events.CancelEvent(SCRIPT_UPDATE_TARGET_LIST);
                            first_outOfCombat_recent = true;
                        }

                        //if the unit's auto attack is ready, they are in range of their target and they are not set to IDLE_MOTION_TYPE due to spell casting
                        if (me->isAttackReady() && me->IsWithinMeleeRange(me->GetVictim()) && !casting)
                        {
                            //melee attack the target
                            me->AttackerStateUpdate(me->GetVictim(), BASE_ATTACK);
                            //reset the auto attack timer
                            me->resetAttackTimer();
                        }

                        //used for handling every combat event
                        switch (entry)
                        {
                        case ID_FLESH_BEHEMOTH:
                            while (uint32 eventId = events.ExecuteEvent())
                            {
                                switch (eventId)
                                {
                                case SCRIPT_FLESH_BEHEMOTH_CAST_STOMP:
                                    fleshBehemoth_cast_stomp();
                                    break;
                                case SCRIPT_FLESH_BEHEMOTH_CONTINUE_AFTER_CAST_STOMP:
                                    fleshBehemoth_continueAfterStomp();
                                    break;
                                case SCRIPT_FLESH_BEHEMOTH_CAST_THUNDERCLAP:
                                    fleshBehemoth_cast_thunderClap();
                                    break;
                                case SCRIPT_UPDATE_TARGET_LIST:
                                    updateInCombatWithList();
                                    break;
                                default:
                                    break;
                                }
                            }

                            break;
                        case ID_RAMPAGING_ABOMINATION:
                            while (uint32 eventId = events.ExecuteEvent())
                            {
                                switch (eventId)
                                {
                                case SCRIPT_RAMPAGING_ABOMINATION_CAST_CLEAVE:
                                {
                                    rampagingAbomination_cast_cleave();
                                    break;
                                }
                                case SCRIPT_RAMPAGING_ABOMINATION_CAST_SCOURGE_HOOK:
                                {
                                    rampagingAbomination_cast_scourge_hook();
                                    break;
                                }
                                case SCRIPT_RAMPAGING_ABOINATION_CONTINUE_AFTER_SCOURGE_HOOK:
                                    rampagingAbomination_continueAfterScourgeHook();
                                    break;
                                case SCRIPT_UPDATE_TARGET_LIST:
                                    updateInCombatWithList();
                                    break;
                                default:
                                    break;
                                }
                            }

                            break;
                        case ID_WARRIOR_OF_THE_FROZEN_WASTES:
                            while (uint32 eventId = events.ExecuteEvent())
                            {
                                switch (eventId)
                                {
                                case SCRIPT_WARRIOR_OF_THE_FROZEN_WASTES_CAST_CLEAVE:
                                {
                                    warriorOfTheFrozenWastes_cast_cleave();
                                    break;
                                }
                                case SCRIPT_UPDATE_TARGET_LIST:
                                    updateInCombatWithList();
                                    break;
                                default:
                                    break;
                                }
                            }

                            break;
                        case ID_KOLTIRA_DEATHWEAVER:
                        case ID_ORBAZ_BLOODBANE:
                        case ID_THASSARIAN:
                            while (uint32 eventId = events.ExecuteEvent())
                            {
                                switch (eventId)
                                {
                                case SCRIPT_DK_CAST_PLAGUE_STRIKE:
                                {
                                    dk_cast_plague_strike();
                                    break;
                                }
                                case SCRIPT_UPDATE_TARGET_LIST:
                                    updateInCombatWithList();
                                    break;
                                default:
                                    break;
                                }
                            }

                            break;
                        case ID_DEFENDER_OF_THE_LIGHT:
                            while (uint32 eventId = events.ExecuteEvent())
                            {
                                switch (eventId)
                                {
                                case SCRIPT_DEFENDER_OF_THE_LIGHT_CAST_HOLY_LIGHT:
                                    defenderOfTheLight_cast_holyLight();
                                    break;
                                case SCRIPT_DEFENDER_OF_THE_LIGHT_CONTINUE_AFTER_HOLY_LIGHT:
                                    defenderOfTheLight_continueAfterHolyLight();
                                    break;
                                case SCRIPT_DEFENDER_OF_THE_LIGHT_CAST_HOLY_STRIKE:
                                    defenderOfTheLight_cast_holyStrike();
                                    break;
                                case SCRIPT_DEFENDER_OF_THE_LIGHT_CAST_UPPERCUT:
                                    defenderOfTheLight_cast_uppercut();
                                    break;
                                case SCRIPT_UPDATE_TARGET_LIST:
                                    updateInCombatWithList();
                                    break;
                                default:
                                    break;
                                }
                            }

                            break;
                        case ID_KORFAX_CHAMPION_OF_THE_LIGHT:
                            while (uint32 eventId = events.ExecuteEvent())
                            {
                                switch (eventId)
                                {
                                case SCRIPT_KORFAX_CHAMPION_OF_THE_LIGHT_CAST_CLEAVE:
                                    korfaxChampionOfTheLight_cast_cleave();
                                    break;
                                case SCRIPT_UPDATE_TARGET_LIST:
                                    updateInCombatWithList();
                                    break;
                                default:
                                    break;
                                }
                            }

                            break;
                        case ID_COMMANDER_ELIGOR_DAWNBRINGER:
                            while (uint32 eventId = events.ExecuteEvent())
                            {
                                switch (eventId)
                                {
                                case SCRIPT_COMMANDER_ELIGOR_DAWNBRINGER_CAST_HOLY_LIGHT:
                                    commanderEligorDawnbringer_cast_holyLight();
                                    break;
                                case SCRIPT_COMMANDER_ELIGOR_DAWNBRINGER_CONTINUE_AFTER_HOLY_LIGHT:
                                    commanderEligorDawnbringer_continueAfterHolyLight();
                                    break;
                                case SCRIPT_UPDATE_TARGET_LIST:
                                    updateInCombatWithList();
                                    break;
                                default:
                                    break;
                                }
                            }

                            break;
                        case ID_RAYNE:
                            while (uint32 eventId = events.ExecuteEvent())
                            {
                                switch (eventId)
                                {
                                case SCRIPT_RAYNE_CAST_REJUVENATION:
                                    rayne_cast_rejuvenation();
                                    break;
                                case SCRIPT_RAYNE_CAST_STARFALL_SETUP:
                                    rayne_cast_starfall_setup();
                                    break;
                                case SCRIPT_RAYNE_CAST_STARFALL:
                                    rayne_cast_starfall();
                                    break;
                                case SCRIPT_RAYNE_CONTINUE_AFTER_STARFALL:
                                    rayne_continueAfterStarfall();
                                    break;
                                case SCRIPT_RAYNE_CAST_WRATH:
                                    rayne_cast_wrath();
                                    break;
                                case SCRIPT_RAYNE_CONTINUE_AFTER_WRATH:
                                    rayne_continueAfterWrath();
                                    break;
                                case SCRIPT_UPDATE_TARGET_LIST:
                                    updateInCombatWithList();
                                    break;
                                default:
                                    break;
                                }
                            }

                            break;
                        case ID_RIMBLAT_EARTHSHATTER:
                            while (uint32 eventId = events.ExecuteEvent())
                            {
                                switch (eventId)
                                {
                                case SCRIPT_RIMBLAT_EARTHSHATTER_CAST_CHAIN_HEAL:
                                    rimblatEarthshatter_cast_chainHeal();
                                    break;
                                case SCRIPT_RIMBLAT_EARTHSHATTER_CONTINUE_AFTER_CHAIN_HEAL:
                                    rimblatEarthshatter_continueAfterChainHeal();
                                    break;
                                case SCRIPT_RIMBLAT_EARTHSHATTER_CAST_THUNDER:
                                    rimblatEarthshatter_cast_thunder();
                                    break;
                                case SCRIPT_UPDATE_TARGET_LIST:
                                    updateInCombatWithList();
                                    break;
                                default:
                                    break;
                                }
                            }

                            break;
                            //this default block is here in case an npc is using this ai that either isn't scripted yet or isn't one of its intended scipties
                            //so they can still perform basic target aquiring and whatnot
                        default:
                            while (uint32 eventId = events.ExecuteEvent())
                            {
                                switch (eventId)
                                {
                                case SCRIPT_UPDATE_TARGET_LIST:
                                    updateInCombatWithList();
                                    break;
                                }
                            }

                            break;
                        }
                    }
                    else if (me->IsInCombat() && !me->GetVictim())
                    {
                        //me->Say("In combat, no target.", LANG_UNIVERSAL);
                        if (first_inCombat_recent)
                        {
                            events.CancelEvent(SCRIPT_UPDATE_TARGET_LIST);
                            first_outOfCombat_recent = true;
                        }
                        Unit *target = me->GetCombatManager().GetAnyTarget();
                        me->GetMotionMaster()->MoveChase(target);
                        me->Attack(target, true);
                    }
                    else if (!me->IsInCombat())
                    {
                        //me->Say("Not in combat.", LANG_UNIVERSAL);
                        //this is to prevent script spamming and potentially bogging down the server with too many updateInCombatWithList() calls
                        if (first_outOfCombat_recent)
                        {
                            me->GetMotionMaster()->Clear();
                            me->GetMotionMaster()->MoveIdle();
                            updateInCombatWithList();
                            events.ScheduleEvent(SCRIPT_UPDATE_TARGET_LIST, 1s);
                            first_outOfCombat_recent = false;
                            first_inCombat_recent = true;
                        }

                        //this block is used to handle in combat events that fire off while not in combat
                        //the general idea here is to continually reschedule the event until the unit is back in combat and then can actually execute the event
                        switch (entry)
                        {
                        case ID_FLESH_BEHEMOTH:
                            while (uint32 eventId = events.ExecuteEvent())
                            {
                                switch (eventId)
                                {
                                case SCRIPT_FLESH_BEHEMOTH_CAST_STOMP:
                                    //me->Say("stomp cast delayed by 1s", LANG_UNIVERSAL);
                                    events.ScheduleEvent(SCRIPT_FLESH_BEHEMOTH_CAST_STOMP, 1s);
                                    break;
                                case SCRIPT_FLESH_BEHEMOTH_CONTINUE_AFTER_CAST_STOMP:
                                    //me->Say("out of combat, rescheduling stomp by full duration", LANG_UNIVERSAL);
                                    events.ScheduleEvent(SCRIPT_FLESH_BEHEMOTH_CAST_STOMP, (TIMER_FLESH_BEHEMOTH_STOMP_FIRST * 1s));
                                    break;
                                case SCRIPT_FLESH_BEHEMOTH_CAST_THUNDERCLAP:
                                    //me->Say("thunderclap cast delayed by 1s", LANG_UNIVERSAL);
                                    events.ScheduleEvent(SCRIPT_FLESH_BEHEMOTH_CAST_THUNDERCLAP, 1s);
                                    break;
                                case SCRIPT_UPDATE_TARGET_LIST:
                                    updateInCombatWithList();
                                    events.ScheduleEvent(SCRIPT_UPDATE_TARGET_LIST, 1s);
                                    break;
                                default:
                                    break;
                                }
                            }

                            break;
                        case ID_RAMPAGING_ABOMINATION:
                            while (uint32 eventId = events.ExecuteEvent())
                            {
                                switch (eventId)
                                {
                                case SCRIPT_RAMPAGING_ABOMINATION_CAST_CLEAVE:
                                {
                                    //me->Say("out of combat, rescheduling cleave by 1s", LANG_UNIVERSAL);
                                    events.ScheduleEvent(SCRIPT_RAMPAGING_ABOMINATION_CAST_CLEAVE, 1s);
                                    break;
                                }
                                case SCRIPT_RAMPAGING_ABOMINATION_CAST_SCOURGE_HOOK:
                                {
                                    //me->Say("out of combat, rescheduling scourge hook by 1s", LANG_UNIVERSAL);
                                    events.ScheduleEvent(SCRIPT_RAMPAGING_ABOMINATION_CAST_SCOURGE_HOOK, 1s);
                                    break;
                                }
                                case SCRIPT_RAMPAGING_ABOINATION_CONTINUE_AFTER_SCOURGE_HOOK:
                                    //me->Say("out of combat, rescheduling scourge hook by full duration", LANG_UNIVERSAL);
                                    events.ScheduleEvent(SCRIPT_RAMPAGING_ABOMINATION_CAST_SCOURGE_HOOK, (TIMER_RAMPAGING_ABOMINATION_SCOURGE_HOOK_FIRST * 1s));
                                    break;
                                case SCRIPT_UPDATE_TARGET_LIST:
                                    updateInCombatWithList();
                                    events.ScheduleEvent(SCRIPT_UPDATE_TARGET_LIST, 1s);
                                    break;
                                default:
                                    break;
                                }
                            }

                            break;
                        case ID_WARRIOR_OF_THE_FROZEN_WASTES:
                            while (uint32 eventId = events.ExecuteEvent())
                            {
                                switch (eventId)
                                {
                                case SCRIPT_WARRIOR_OF_THE_FROZEN_WASTES_CAST_CLEAVE:
                                {
                                    //me->Say("out of combat, rescheduling cleave by 1s", LANG_UNIVERSAL);
                                    events.ScheduleEvent(SCRIPT_WARRIOR_OF_THE_FROZEN_WASTES_CAST_CLEAVE, 1s);
                                    break;
                                }
                                case SCRIPT_UPDATE_TARGET_LIST:
                                    updateInCombatWithList();
                                    events.ScheduleEvent(SCRIPT_UPDATE_TARGET_LIST, 1s);
                                    break;
                                default:
                                    break;
                                }
                            }

                            break;
                        case ID_KOLTIRA_DEATHWEAVER:
                        case ID_ORBAZ_BLOODBANE:
                        case ID_THASSARIAN:
                            while (uint32 eventId = events.ExecuteEvent())
                            {
                                switch (eventId)
                                {
                                case SCRIPT_DK_CAST_PLAGUE_STRIKE:
                                {
                                    //me->Say("out of combat, rescheduling plague strike by 1s", LANG_UNIVERSAL);
                                    events.ScheduleEvent(SCRIPT_DK_CAST_PLAGUE_STRIKE, 1s);
                                    break;
                                }
                                case SCRIPT_UPDATE_TARGET_LIST:
                                    updateInCombatWithList();
                                    events.ScheduleEvent(SCRIPT_UPDATE_TARGET_LIST, 1s);
                                    break;
                                default:
                                    break;
                                }
                            }

                            break;
                        case ID_DEFENDER_OF_THE_LIGHT:
                            while (uint32 eventId = events.ExecuteEvent())
                            {
                                switch (eventId)
                                {
                                case SCRIPT_DEFENDER_OF_THE_LIGHT_CAST_HOLY_LIGHT:
                                    //me->Say("out of combat, rescheduling holy light by 1s", LANG_UNIVERSAL);
                                    events.ScheduleEvent(SCRIPT_DEFENDER_OF_THE_LIGHT_CAST_HOLY_LIGHT, 1s);
                                    break;
                                case SCRIPT_DEFENDER_OF_THE_LIGHT_CONTINUE_AFTER_HOLY_LIGHT:
                                    //me->Say("out of combat, rescheduling holy light by full duration", LANG_UNIVERSAL);
                                    events.ScheduleEvent(SCRIPT_DEFENDER_OF_THE_LIGHT_CAST_HOLY_LIGHT, (TIMER_DEFENDER_OF_THE_LIGHT_HOLY_LIGHT_FIRST * 1s));
                                    break;
                                case SCRIPT_DEFENDER_OF_THE_LIGHT_CAST_HOLY_STRIKE:
                                    //me->Say("out of combat, rescheduling holy strike by 1s", LANG_UNIVERSAL);
                                    events.ScheduleEvent(SCRIPT_DEFENDER_OF_THE_LIGHT_CAST_HOLY_STRIKE, 1s);
                                    break;
                                case SCRIPT_DEFENDER_OF_THE_LIGHT_CAST_UPPERCUT:
                                    //me->Say("out of combat, rescheduling uppercut by 1s", LANG_UNIVERSAL);
                                    events.ScheduleEvent(SCRIPT_DEFENDER_OF_THE_LIGHT_CAST_UPPERCUT, 1s);
                                    break;
                                case SCRIPT_UPDATE_TARGET_LIST:
                                    updateInCombatWithList();
                                    events.ScheduleEvent(SCRIPT_UPDATE_TARGET_LIST, 1s);
                                    break;
                                default:
                                    break;
                                }
                            }

                            break;
                        case ID_KORFAX_CHAMPION_OF_THE_LIGHT:
                            while (uint32 eventId = events.ExecuteEvent())
                            {
                                switch (eventId)
                                {
                                case SCRIPT_KORFAX_CHAMPION_OF_THE_LIGHT_CAST_CLEAVE:
                                    //me->Say("out of combat, rescheduling cleave by 1s", LANG_UNIVERSAL);
                                    events.ScheduleEvent(SCRIPT_KORFAX_CHAMPION_OF_THE_LIGHT_CAST_CLEAVE, 1s);
                                    break;
                                case SCRIPT_UPDATE_TARGET_LIST:
                                    updateInCombatWithList();
                                    events.ScheduleEvent(SCRIPT_UPDATE_TARGET_LIST, 1s);
                                    break;
                                default:
                                    break;
                                }
                            }

                            break;
                        case ID_COMMANDER_ELIGOR_DAWNBRINGER:
                            while (uint32 eventId = events.ExecuteEvent())
                            {
                                switch (eventId)
                                {
                                case SCRIPT_COMMANDER_ELIGOR_DAWNBRINGER_CAST_HOLY_LIGHT:
                                    //me->Say("out of combat, rescheduling holy light by 1s", LANG_UNIVERSAL);
                                    events.ScheduleEvent(SCRIPT_COMMANDER_ELIGOR_DAWNBRINGER_CAST_HOLY_LIGHT, 1s);
                                    break;
                                case SCRIPT_COMMANDER_ELIGOR_DAWNBRINGER_CONTINUE_AFTER_HOLY_LIGHT:
                                    //me->Say("out of combat, rescheduling holy light by full duration", LANG_UNIVERSAL);
                                    events.ScheduleEvent(SCRIPT_COMMANDER_ELIGOR_DAWNBRINGER_CAST_HOLY_LIGHT, (TIMER_COMMANDER_ELIGOR_DAWNBRINGER_HOLY_LIGHT_FIRST * 1s));
                                    break;
                                case SCRIPT_UPDATE_TARGET_LIST:
                                    updateInCombatWithList();
                                    events.ScheduleEvent(SCRIPT_UPDATE_TARGET_LIST, 1s);
                                    break;
                                default:
                                    break;
                                }
                            }

                            break;
                        case ID_RAYNE:
                            while (uint32 eventId = events.ExecuteEvent())
                            {
                                switch (eventId)
                                {
                                case SCRIPT_RAYNE_CAST_REJUVENATION:
                                    //me->Say("out of combat, rescheduling rejuvenation by 1s", LANG_UNIVERSAL);
                                    events.ScheduleEvent(SCRIPT_RAYNE_CAST_REJUVENATION, 1s);
                                    break;
                                case SCRIPT_RAYNE_CAST_STARFALL_SETUP:
                                    //me->Say("out of combat, rescheduling starfall by 1s", LANG_UNIVERSAL);
                                    events.ScheduleEvent(SCRIPT_RAYNE_CAST_STARFALL_SETUP, 1s);
                                    break;
                                case SCRIPT_RAYNE_CAST_STARFALL:
                                    //me->Say("out of combat, rescheduling starfall by full duration", LANG_UNIVERSAL);
                                    events.ScheduleEvent(SCRIPT_RAYNE_CAST_STARFALL_SETUP, (TIMER_RAYNE_STARFALL_FIRST * 1s));
                                    break;
                                case SCRIPT_RAYNE_CONTINUE_AFTER_STARFALL:
                                    //me->Say("out of combat, rescheduling starfall by full duration", LANG_UNIVERSAL);
                                    events.ScheduleEvent(SCRIPT_RAYNE_CAST_STARFALL_SETUP, (TIMER_RAYNE_STARFALL_FIRST * 1s));
                                    break;
                                case SCRIPT_RAYNE_CAST_WRATH:
                                    //me->Say("out of combat, rescheduling wrath by 1s", LANG_UNIVERSAL);
                                    events.ScheduleEvent(SCRIPT_RAYNE_CAST_WRATH, 1s);
                                    break;
                                case SCRIPT_RAYNE_CONTINUE_AFTER_WRATH:
                                    //me->Say("out of combat, rescheduling wrath by full duration", LANG_UNIVERSAL);
                                    events.ScheduleEvent(SCRIPT_RAYNE_CAST_WRATH, (TIMER_RAYNE_WRATH_FIRST * 1s));
                                    break;
                                case SCRIPT_UPDATE_TARGET_LIST:
                                    updateInCombatWithList();
                                    events.ScheduleEvent(SCRIPT_UPDATE_TARGET_LIST, 1s);
                                    break;
                                default:
                                    break;
                                }
                            }

                            break;
                        case ID_RIMBLAT_EARTHSHATTER:
                            while (uint32 eventId = events.ExecuteEvent())
                            {
                                switch (eventId)
                                {
                                case SCRIPT_RIMBLAT_EARTHSHATTER_CAST_CHAIN_HEAL:
                                    //me->Say("out of combat, rescheduling chain heal by 1s", LANG_UNIVERSAL);
                                    events.ScheduleEvent(SCRIPT_RIMBLAT_EARTHSHATTER_CAST_CHAIN_HEAL, 1s);
                                    break;
                                case SCRIPT_RIMBLAT_EARTHSHATTER_CONTINUE_AFTER_CHAIN_HEAL:
                                    //me->Say("out of combat, rescheduling chain heal by full duration", LANG_UNIVERSAL);
                                    events.ScheduleEvent(SCRIPT_RIMBLAT_EARTHSHATTER_CAST_CHAIN_HEAL, (TIMER_RIMBLAT_EARTHSHATTER_CHAIN_HEAL_FIRST * 1s));
                                    break;
                                case SCRIPT_RIMBLAT_EARTHSHATTER_CAST_THUNDER:
                                    //me->Say("out of combat, rescheduling thunder by 1s", LANG_UNIVERSAL);
                                    events.ScheduleEvent(SCRIPT_RIMBLAT_EARTHSHATTER_CAST_THUNDER, 1s);
                                    break;
                                case SCRIPT_UPDATE_TARGET_LIST:
                                    updateInCombatWithList();
                                    events.ScheduleEvent(SCRIPT_UPDATE_TARGET_LIST, 1s);
                                    break;
                                default:
                                    break;
                                }
                            }

                            break;
                            //this default block is here in case an npc is using this ai that either isn't scripted yet or isn't one of its intended scipties
                            //so they can still perform basic target aquiring and whatnot
                        default:
                            while (uint32 eventId = events.ExecuteEvent())
                            {
                                switch (eventId)
                                {
                                case SCRIPT_UPDATE_TARGET_LIST:
                                    updateInCombatWithList();
                                    events.ScheduleEvent(SCRIPT_UPDATE_TARGET_LIST, 1s);
                                    break;
                                }
                            }

                            break;
                        }
                    }
                }
                else if (me->GetReactState() == REACT_PASSIVE)
                {
                    if (me->IsInCombat() && me->GetVictim())
                    {
                        if (me->isAttackReady() && me->IsWithinMeleeRange(me->GetVictim()) && !casting)
                        {
                            //melee attack the target
                            me->AttackerStateUpdate(me->GetVictim(), BASE_ATTACK);
                            //reset the auto attack timer
                            me->resetAttackTimer();
                        }
                    }

                    while (uint32 eventId = events.ExecuteEvent())
                    {
                        switch (eventId)
                        {
                        case SCRIPT_HIT_BY_APOCALYPSE_SET_KNOCKDOWN:
                            me->GetMotionMaster()->Clear();
                            me->GetMotionMaster()->MoveIdle();
                            me->CombatStop();
                            me->GetCombatManager().EndAllCombat();
                            me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STAND_STATE_NONE);
                            me->HandleEmoteCommand(EMOTE_STAND_STATE_NONE);
                            me->CastSpell(me, SPELL_APOCALYPSE_SECONDARY, true);
                            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_PACIFIED | UNIT_FLAG_NOT_SELECTABLE);
                            break;
                        default:
                            break;
                        }
                    }
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_MASTER_darion_summoned_unitAI(creature);
    }
};

class spell_chapter5_apocalypse : public SpellScriptLoader
{
public:
    spell_chapter5_apocalypse() : SpellScriptLoader("spell_chapter5_apocalypse") { }

    class spell_chapter5_apocalypse_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_chapter5_apocalypse_SpellScript);

        void targetSelection_Override(std::list<WorldObject*>& targets)
        {
            for (std::list<WorldObject*>::iterator itr = targets.begin(); itr != targets.end(); ++itr)
            {
                if (Player *player = (*itr)->ToPlayer())
                {
                    targets.erase(itr);
                }
                else if (uint32 entry = (*itr)->ToCreature()->GetEntry())
                {
                    switch (entry)
                    {
                    case ID_THE_LICH_KING:
                    case ID_HIGHLORD_DARION_MOGRAINE:
                    case ID_KOLTIRA_DEATHWEAVER:
                    case ID_THASSARIAN:
                    case ID_HIGHLORD_TIRION_FORDRING:
                        targets.erase(itr);
                        break;
                    }
                }
            }
        }

        void Register() override
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_chapter5_apocalypse_SpellScript::targetSelection_Override, 0, 7);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_chapter5_apocalypse_SpellScript();
    }
};

class spell_chapter5_apocalypse_secondary : public SpellScriptLoader
{
public:
    spell_chapter5_apocalypse_secondary() : SpellScriptLoader("spell_chapter5_apocalypse_secondary") { }

    class spell_chapter5_apocalypse_secondary_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_chapter5_apocalypse_secondary_SpellScript);

        void targetSelection_Override(std::list<WorldObject*>& targets)
        {
            for (std::list<WorldObject*>::iterator itr = targets.begin(); itr != targets.end(); ++itr)
            {
                if (Creature *caster = GetCaster()->ToCreature())
                {
                    if (!((*itr)->GetGUID() == caster->GetGUID()))
                    {
                        targets.erase(itr);
                    }
                }
                else if (Player *player = GetCaster()->ToPlayer())
                {
                    targets.erase(itr);
                }
            }
        }

        void Register() override
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_chapter5_apocalypse_secondary_SpellScript::targetSelection_Override, 0, 7);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_chapter5_apocalypse_secondary_SpellScript();
    }
};

class spell_chapter5_light_of_dawn_kill : public SpellScriptLoader
{
public:
    spell_chapter5_light_of_dawn_kill() : SpellScriptLoader("spell_chapter5_light_of_dawn_kill") { }

    class spell_chapter5_light_of_dawn_kill_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_chapter5_light_of_dawn_kill_SpellScript);

        void alterDamage_toLethal(SpellEffIndex effIndex)
        {
            if (Creature *hitCreature = this->GetHitUnit()->ToCreature())
            {
                this->PreventHitDamage();
                GetCaster()->Kill(GetCaster(), hitCreature, false);
            }
        }

        void targetSelection_Override(std::list<WorldObject*>& targets)
        {
            for (std::list<WorldObject*>::iterator itr = targets.begin(); itr != targets.end(); ++itr)
            {
                if (Player *player = (*itr)->ToPlayer())
                {
                    targets.erase(itr);
                }
                else if (uint32 entry = (*itr)->ToCreature()->GetEntry())
                {
                    switch (entry)
                    {
                    case ID_HIGHLORD_DARION_MOGRAINE:
                    case ID_KOLTIRA_DEATHWEAVER:
                    case ID_ORBAZ_BLOODBANE:
                    case ID_THASSARIAN:
                    case ID_HIGHLORD_TIRION_FORDRING:
                    case ID_DEFENDER_OF_THE_LIGHT:
                    case ID_LORD_MAXWELL_TYROSUS:
                    case ID_KORFAX_CHAMPION_OF_THE_LIGHT:
                    case ID_LEONID_BARTHALOMEW_THE_REVERED:
                    case ID_DUKE_NICHOLAS_ZVERENHOFF:
                    case ID_COMMANDER_ELIGOR_DAWNBRINGER:
                    case ID_RAYNE:
                    case ID_RIMBLAT_EARTHSHATTER:
                    case 28534:
                        targets.erase(itr);
                        break;
                    }
                }
            }
        }

        void Register() override
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_chapter5_light_of_dawn_kill_SpellScript::targetSelection_Override, 0, 7);
            OnEffectHitTarget += SpellEffectFn(spell_chapter5_light_of_dawn_kill_SpellScript::alterDamage_toLethal, 0, SPELL_EFFECT_SCHOOL_DAMAGE);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_chapter5_light_of_dawn_kill_SpellScript();
    }
};

void AddSC_the_scarlet_enclave_c5()
{
    new npc_highlord_darion_mograine();
    new npc_MASTER_darion_summoned_unit();
    new spell_chapter5_light_of_dawn_kill();
    new spell_chapter5_apocalypse();
    new spell_chapter5_apocalypse_secondary();
}
