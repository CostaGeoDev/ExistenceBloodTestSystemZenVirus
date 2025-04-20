modded class ActionTestBloodSelf
{
    void ActionTestBloodSelf()
	{
		m_CallbackClass = ActionTestBloodSelfCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_CRAFTING;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_LOW;
	}
	
	override void CreateConditionComponents()  
	{	
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTSelf;
	}

	override bool HasTarget()
	{
		return false;
	}
		
	override string GetText()
	{
		return "#test_blood";
	}
	
	string hpstatus ( int X )
	{
		if (X == 0) return "No trace";
		if (X > 0 && X < 200) return "Initial stage";
		if (X >= 200 && X < 700) return "Middle stage";
		if (X >= 700 && X <= 1000) return "Final stage";
		return "Unknown stage"; // Ensures a default return value for unexpected cases
	}

	override void OnFinishProgressServer( ActionData action_data )
	{	
		PluginLifespan module_lifespan = PluginLifespan.Cast( GetPlugin( PluginLifespan ) );
		int blood_type = action_data.m_Player.GetStatBloodType().Get();
		
		module_lifespan.UpdateBloodType( action_data.m_Player, blood_type );
		module_lifespan.UpdateBloodTypeVisibility( action_data.m_Player, true );
		
		action_data.m_MainItem.Delete();
		action_data.m_Player.GetSoftSkillsManager().AddSpecialty( m_SpecialtyWeight );


		EStatLevels immunityLevel = action_data.m_Player.GetImmunityLevel();
		string immunityLevelStr;
		switch (immunityLevel)
		{
			case EStatLevels.GREAT: immunityLevelStr = "BEST"; break;
			case EStatLevels.HIGH: immunityLevelStr = "HIGH"; break;
			case EStatLevels.MEDIUM: immunityLevelStr = "MEDIUM"; break;
			case EStatLevels.LOW: immunityLevelStr = "LOW"; break;
			case EStatLevels.CRITICAL: immunityLevelStr = "CRITICAL"; break;
			default: immunityLevelStr = "UNKNOWN"; break;
		}

		SendMessageToClient(action_data.m_Player, "Your Medical Report:");
		SendMessageToClient(action_data.m_Player, "Immunity Level: " + immunityLevelStr);
		SendMessageToClient(action_data.m_Player, "Cholera: " + action_data.m_Player.GetSingleAgentCount(eAgents.CHOLERA).ToString());
		SendMessageToClient(action_data.m_Player, "Brain Disease: " + hpstatus(action_data.m_Player.GetSingleAgentCount(eAgents.BRAIN)));
		const int PNEUMONIA_THRESHOLD = 1150;
		int influenzaCount = action_data.m_Player.GetSingleAgentCount(eAgents.INFLUENZA);

		SendMessageToClient(action_data.m_Player, "Influenza: " + hpstatus(influenzaCount));

		if (influenzaCount >= PNEUMONIA_THRESHOLD)
		{
			SendMessageToClient(action_data.m_Player, "Pneumonia: " + hpstatus(influenzaCount));
		}		
		SendMessageToClient(action_data.m_Player, "Salmonella: " + hpstatus(action_data.m_Player.GetSingleAgentCount(eAgents.SALMONELLA)));
		SendMessageToClient(action_data.m_Player, "Wound Infection: " + hpstatus(action_data.m_Player.GetSingleAgentCount(eAgents.WOUND_AGENT)));
		SendMessageToClient(action_data.m_Player, "Heavy Metal: " + hpstatus(action_data.m_Player.GetSingleAgentCount(eAgents.HEAVYMETAL)));
		SendMessageToClient(action_data.m_Player, "Chemical Poisoning: " + hpstatus(action_data.m_Player.GetSingleAgentCount(eAgents.CHEMICAL_POISON)));
		SendMessageToClient(action_data.m_Player, "Zen Virus: " + hpstatus(action_data.m_Player.GetSingleAgentCount(VirusAgents.VIRUS)));
		
		action_data.m_MainItem.AddHealth("", "", -4);
        
		if (action_data.m_MainItem.GetHealth("GlobalHealth", "Health") < 1)
        {
        action_data.m_MainItem.Delete();
        }
	}	
};