/*
 * Copyright (C) 2010 - 2012 ProjectSkyfire <http://www.projectskyfire.org/>
 * 
 * Copyright (C) 2011 - 2012 ArkCORE <http://www.arkania.net/>
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

#include"ScriptPCH.h"
#include"WorldPacket.h"
#include"lost_city_of_the_tolvir.h"
enum Spells 
{
    SPELL_DEFLECT_SHIELD                          = 84589,
    SPELL_STORM_BOLT                              = 73564,
    SPELL_ABSSORB_STORM                           = 83151,
    SPELL_SUMMON_CLOUD_BURST                      = 83790,
    // this adds
    SPELL_DEPLETION                               = 84550,
    SPELL_CHAIN_LIGHTNING                         = 83455,

    SPELL_LIGHTNING_NOVA                          = 84544,
    SPELL_THUNDER_CRASH                           = 84522,
    SPELL_LIGHTINING_CHARGE                       = 91871,

    SPELL_CLOUD_BURST_VISUAL                      = 83048,
    SPELL_CLOUD_BURST                             = 83051,
}

enum Events 
{
    EVENT_DEFLECT_SHIELD = 1,
    EVENT_STORM_BOLT,
    EVENT_ABSSORB_STORM,
    EVENT_SUMMON_CLOUD_BURST,
    EVENT_SUMMON_MINION,
    EVENT_SUMMON_SERVANT,
};

class boss_siamat: public CreatureScript 
{
public:
    boss_siamat() : CreatureScript("boss_siamat") { }

    CreatureAI* GetAI(Creature* pCreature) const 
    {
        return new boss_siamatAI(pCreature);
    }

    struct boss_siamatAI: public BossAI 
    {
        boss_siamatAI(Creature* pCreature) : BossAI(pCreature, DATA_SIAMAT_EVENT), Summons(me)
        {
            pInstance = pCreature->GetInstanceScript();
        }

        InstanceScript* pInstance;
        EventMap events;
        SummonList Summons;
        uint8 servantCount;
        uint8 servantDeaths;
        uint8 phase;

        void Reset() 
        {
            events.Reset();
            Summons.DespawnAll();
            servantCount = 0;
            servantDeaths = 0;
            phase = 1;

            if (pInstance)
                pInstance->SetData(DATA_SIAMAT_EVENT, NOT_STARTED);
        }