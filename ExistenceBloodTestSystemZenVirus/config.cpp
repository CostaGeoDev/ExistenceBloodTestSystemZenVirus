class CfgPatches
{
	class BloodTesting
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Scripts",
			"DZ_Data",
			"ZenVirus"
		};
	};
};
class CfgMods
{
	class BloodTesting
	{
		dir="ExistenceBloodTestSystemZenVirus";
		picture="";
		action="";
		hideName=1;
		hidePicture=1;
		name="ExistenceBloodTestSystemZenVirus";
		credits="CostaGeo";
		author="";
		authorID="0";
		version="1.0";
		extra=0;
		type="mod";
		inputs="";
		dependencies[]=
		{
			"Game",
			"World",
			"Mission"
		};
		class defs
		{
			class gameScriptModule
			{
				value="";
				files[]=
				{
					"ExistenceBloodTestSystemZenVirus/Scripts/3_Game"
				};
			};
			class worldScriptModule
			{
				value="";
				files[]=
				{
					"ExistenceBloodTestSystemZenVirus/Scripts/4_World"
				};
			};
			class missionScriptModule
			{
				value="";
				files[]=
				{
					"ExistenceBloodTestSystemZenVirus/Scripts/5_Mission"
				};
			};
		};
	};
};
