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
#include <ctime>

/*
serophis Today at 12:39 AM:
Also are you good picking 24 good pets/mounts ?

Donk Shartfarger Today at 12:39 AM:
Yeah, i think so
What do you want the divide to be
12 and 12?

serophis Today at 12:39 AM:
Nah
6 and 18

Donk Shartfarger Today at 12:40 AM:
How do you want them spread out?

serophis Today at 12:40 AM:
3 ground, 3 flying, 18 pets

Donk Shartfarger Today at 12:40 AM:
Alright, what about in terms of hourage

serophis Today at 12:40 AM:
Ground at hour 8 16 and 24 I guess and flying at 4 12 and 20

Donk Shartfarger Today at 12:41 AM:
okay, it starts from zero so I'll do that
*/

enum rewards_by_hour_value
{
    REWARD_HOUR_0 = 13584, //Diablo Stone //classic pet
    REWARD_HOUR_1 = 39656, //Tyrael's Hilt //tbc pet
    REWARD_HOUR_2 = 56806, //Mini Thor //wotlk pet
    REWARD_HOUR_3 = 54811, //Celestial Steed //flying mount
    REWARD_HOUR_4 = 13582, //Zergling Leash //classic pet
    REWARD_HOUR_5 = 35227, //Goblin Weather Machine - Prototype 01-B //tbc pet
    REWARD_HOUR_6 = 49343, //Spectral Tiger Cub //wotlk pet
    REWARD_HOUR_7 = 21176, //Black Qiraji Resonating Crystal //ground mount
    REWARD_HOUR_8 = 13583, //Panda Collar //classic pet
    REWARD_HOUR_9 = 32498, //Fortune Coin //tbc pet
    REWARD_HOUR_10 = 39286, //Frosty's Collar //wotlk pet
    REWARD_HOUR_11 = 37012, //The Horseman's Reins //flying mount
    REWARD_HOUR_12 = 20371, //Blue Murloc Egg //classic pet
    REWARD_HOUR_13 = 34492, //Rocket Chicken //tbc pet
    REWARD_HOUR_14 = 49662, //Gryphon Hatchling //wotlk pet
    REWARD_HOUR_15 = 43599, //Big Blizzard Bear //ground mount
    REWARD_HOUR_16 = 19054, //Red Dragon Orb //classic pet
    REWARD_HOUR_17 = 38050, //Soul-Trader Beacon //tbc pet
    REWARD_HOUR_18 = 49663, //Wind Rider Cub //wotlk pet
    REWARD_HOUR_19 = 54860, //X-53 Touring Rocket //flying mount
    REWARD_HOUR_20 = 19055, //Green Dragon Orb //classic pet
    REWARD_HOUR_21 = 37297, //Gold Medallion //tbc pet
    REWARD_HOUR_22 = 44819, //Baby Blizzard Bear //wotlk pet
    REWARD_HOUR_23 = 37719, //Swift Zhevra //ground mount
};

enum npc_text_id
{
    TEXT_ID_GREETING = 100000,
    TEXT_ID_HOUR_0 = 100001,
    TEXT_ID_HOUR_1 = 100002,
    TEXT_ID_HOUR_2 = 100003,
    TEXT_ID_HOUR_3 = 100004,
    TEXT_ID_HOUR_4 = 100005,
    TEXT_ID_HOUR_5 = 100006,
    TEXT_ID_HOUR_6 = 100007,
    TEXT_ID_HOUR_7 = 100008,
    TEXT_ID_HOUR_8 = 100009,
    TEXT_ID_HOUR_9 = 100010,
    TEXT_ID_HOUR_10 = 100011,
    TEXT_ID_HOUR_11 = 100012,
    TEXT_ID_HOUR_12 = 100013,
    TEXT_ID_HOUR_13 = 100014,
    TEXT_ID_HOUR_14 = 100015,
    TEXT_ID_HOUR_15 = 100016,
    TEXT_ID_HOUR_16 = 100017,
    TEXT_ID_HOUR_17 = 100018,
    TEXT_ID_HOUR_18 = 100019,
    TEXT_ID_HOUR_19 = 100020,
    TEXT_ID_HOUR_20 = 100021,
    TEXT_ID_HOUR_21 = 100022,
    TEXT_ID_HOUR_22 = 100023,
    TEXT_ID_HOUR_23 = 100024
};

enum gossip_option
{
    PLAYER_ASK_FOR_ITEM = 1001,
    PLAYER_GOODBYE = 1002
};

class npc_sair_o_phess : public CreatureScript
{
public:
    npc_sair_o_phess() : CreatureScript("npc_sair_o_phess") { }

    struct npc_sair_o_phessAI : public ScriptedAI
    {
        //called when the creature is first instantiated either by first spawn or respawn
        npc_sair_o_phessAI(Creature* creature) : ScriptedAI(creature) {}

        //called when the creature's AI is destroyed either by the creature despawning or script hotswapping
        ~npc_sair_o_phessAI(void) override {}

        //return the hour of the day based on system time
        unsigned int getHourOfDay(void)
        {
            //get system time
            time_t currentTime = time(0);

            //get system time info in struct we can easily get the hour from
            tm *ltm = localtime(&currentTime);

            return ltm->tm_hour;
        }

        //determine the item id of the reward based on getHourOfDay()
        unsigned int determineReward(unsigned int hour)
        {
            switch (hour)
            {
            case 0:
                return REWARD_HOUR_0;
                break;
            case 1:
                return REWARD_HOUR_1;
                break;
            case 2:
                return REWARD_HOUR_2;
                break;
            case 3:
                return REWARD_HOUR_3;
                break;
            case 4:
                return REWARD_HOUR_4;
                break;
            case 5:
                return REWARD_HOUR_5;
                break;
            case 6:
                return REWARD_HOUR_6;
                break;
            case 7:
                return REWARD_HOUR_7;
                break;
            case 8:
                return REWARD_HOUR_8;
                break;
            case 9:
                return REWARD_HOUR_9;
                break;
            case 10:
                return REWARD_HOUR_10;
                break;
            case 11:
                return REWARD_HOUR_11;
                break;
            case 12:
                return REWARD_HOUR_12;
                break;
            case 13:
                return REWARD_HOUR_13;
                break;
            case 14:
                return REWARD_HOUR_14;
                break;
            case 15:
                return REWARD_HOUR_15;
                break;
            case 16:
                return REWARD_HOUR_16;
                break;
            case 17:
                return REWARD_HOUR_17;
                break;
            case 18:
                return REWARD_HOUR_18;
                break;
            case 19:
                return REWARD_HOUR_19;
                break;
            case 20:
                return REWARD_HOUR_20;
                break;
            case 21:
                return REWARD_HOUR_21;
                break;
            case 22:
                return REWARD_HOUR_22;
                break;
            case 23:
                return REWARD_HOUR_23;
                break;
            }
        }

        //determine the npc_text to send the player based on getHourOfDay()
        unsigned int determineNpcTextForGossip(unsigned int hour)
        {
            switch (hour)
            {
            case 0:
                return TEXT_ID_HOUR_0;
                break;
            case 1:
                return TEXT_ID_HOUR_1;
                break;
            case 2:
                return TEXT_ID_HOUR_2;
                break;
            case 3:
                return TEXT_ID_HOUR_3;
                break;
            case 4:
                return TEXT_ID_HOUR_4;
                break;
            case 5:
                return TEXT_ID_HOUR_5;
                break;
            case 6:
                return TEXT_ID_HOUR_6;
                break;
            case 7:
                return TEXT_ID_HOUR_7;
                break;
            case 8:
                return TEXT_ID_HOUR_8;
                break;
            case 9:
                return TEXT_ID_HOUR_9;
                break;
            case 10:
                return TEXT_ID_HOUR_10;
                break;
            case 11:
                return TEXT_ID_HOUR_11;
                break;
            case 12:
                return TEXT_ID_HOUR_12;
                break;
            case 13:
                return TEXT_ID_HOUR_13;
                break;
            case 14:
                return TEXT_ID_HOUR_14;
                break;
            case 15:
                return TEXT_ID_HOUR_15;
                break;
            case 16:
                return TEXT_ID_HOUR_16;
                break;
            case 17:
                return TEXT_ID_HOUR_17;
                break;
            case 18:
                return TEXT_ID_HOUR_18;
                break;
            case 19:
                return TEXT_ID_HOUR_19;
                break;
            case 20:
                return TEXT_ID_HOUR_20;
                break;
            case 21:
                return TEXT_ID_HOUR_21;
                break;
            case 22:
                return TEXT_ID_HOUR_22;
                break;
            case 23:
                return TEXT_ID_HOUR_23;
                break;
            }
        }

        //triggered when the player selects a gossip option recieved from this npc
        bool GossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
        {
            //determine which gossip action the player selected
            uint32 gossip_option = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
            //remove any extra options added to this creatures gossip menu for the player
            ClearGossipMenuFor(player);
            //gossip_option switch
            switch (gossip_option)
            {
                case PLAYER_ASK_FOR_ITEM:
                {
                    //get the current hour
                    unsigned int hour = getHourOfDay();
                    //add gossip option of ID PLAYER_GOODBYE
                    AddGossipItemFor(player, 0, "Thanks again, Sair.", GOSSIP_SENDER_MAIN, PLAYER_GOODBYE);
                    //send gossip text depending on what hour it is
                    SendGossipMenuFor(player, determineNpcTextForGossip(hour), me->GetGUID());
                    //give player an item depending on what hour it is
                    player->AddItem(determineReward(hour), 1);
                    break;
                }
                case PLAYER_GOODBYE:
                {
                    //close gossip
                    CloseGossipMenuFor(player);
                    //create a string that says "My pleasure, (player name)."
                    std::string response = "My pleasure, " + player->GetName() + ".";
                    me->Say(response, LANG_UNIVERSAL);
                    me->HandleEmoteCommand(EMOTE_ONESHOT_BOW);
                }
            }

            return true;
        }

        //triggered on player right click while npc has gossip flag
        bool GossipHello(Player* player) override
        {
            //add gossip option of ID PLAYER_ASK_FOR_ITEM
            AddGossipItemFor(player, 0, "Thanks, Sair. What do you have for us this hour?", GOSSIP_SENDER_MAIN, PLAYER_ASK_FOR_ITEM);
            //send gossip text TEXT_ID_GREETING
            SendGossipMenuFor(player, TEXT_ID_GREETING, me->GetGUID());
            return true;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_sair_o_phessAI(creature);
    }
};

void AddSC_sair_o_phess()
{
    new npc_sair_o_phess();
}
