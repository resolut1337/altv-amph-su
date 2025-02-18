#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "crypt32.lib")
#pragma comment(lib, "Wldap32.Lib")
#include <D:\sourca\Loader\libs\CryptoPP\aes.h>
#include <D:\sourca\Loader\libs\CryptoPP\modes.h>
#include <D:\sourca\Loader\libs\CryptoPP\base64.h>
#pragma comment(lib, "D:/sourca/Loader/libs/cryptlib.lib")
namespace aes
{
	__forceinline std::string encrypt(const std::string& str, const std::string& cipher_key, const std::string& iv_key)
	{
		std::string str_out;

		CryptoPP::CFB_Mode<CryptoPP::AES>::Encryption encryption((BYTE*)cipher_key.c_str(), cipher_key.length(), (BYTE*)iv_key.c_str());

		CryptoPP::StringSource encryptor(str, true,
			new CryptoPP::StreamTransformationFilter(encryption,
				new CryptoPP::Base64Encoder(
					new CryptoPP::StringSink(str_out),
					false
				)
			)
		);
		return str_out;
	}
	__forceinline std::string decrypt(const std::string& str, const std::string& cipher_key, const std::string& iv_key)
	{
		std::string str_out;

		CryptoPP::CFB_Mode<CryptoPP::AES>::Decryption decryption((BYTE*)cipher_key.c_str(), cipher_key.length(), (BYTE*)iv_key.c_str());

		CryptoPP::StringSource decryptor(str, true,
			new CryptoPP::Base64Decoder(
				new CryptoPP::StreamTransformationFilter(decryption,
					new CryptoPP::StringSink(str_out)
				)
			)
		);
		return str_out;
	}
}


/* windows includes */
#include <string>
#include <vector>
#include <iostream>

/* dependency includes */
#include "cpr/cpr.h"
#include "fmt/core.h"
#include "json/json.hpp"

struct Auth_t
{
	bool success;

	struct User_t
	{
		std::string about;
		bool activity_visible;
		int age;
		std::vector<int> alert_optout; /* i guess its an integer? */
		std::string allow_post_profile;
		std::string allow_receive_news_feed;
		std::string allow_send_personal_conversation;
		std::string allow_view_identities;
		std::string allow_view_profile;
		struct AvatarUrls_t
		{
			std::string o, h, l, m, s;
		} avatar_urls;
		bool can_ban;
		bool can_converse;
		bool can_edit;
		bool can_follow;
		bool can_ignore;
		bool can_post_profile;
		bool can_view_profile;
		bool can_view_profile_posts;
		bool can_warn;
		bool content_show_signature;
		std::string creation_watch_state;
		struct CustomFields_t
		{
			std::string skype, facebook, twitter;
		} custom_fields;
		std::string custom_title;
		struct DateOfBirth_t
		{
			int year, month, day;
		} dob;
		std::string email;
		bool email_on_conversation;
		std::string gravatar;
		std::string interaction_watch_state;
		bool is_admin;
		bool is_banned;
		bool is_discouraged;
		bool is_moderator;
		bool is_staff;
		bool is_super_admin;
		int last_activity;
		std::string location;
		int message_count;
		struct ProfileBannerUrls_t
		{
			std::string m, l;
		} profile_banner_urls;
		bool push_on_conversation;
		std::vector<int> push_optout; /* i guess integer again? */
		int question_solution_count;
		int reaction_score;
		bool receive_admin_email;
		int register_date;
		std::vector<int> secondary_group_ids; /* thats an int for sure */
		bool show_dob_date;
		bool show_dob_year;
		std::string signature;
		std::string timezone;
		int trophy_points;
		bool usa_tfa; /* can be a array apperently? + typo from xenforo */
		int user_group_id;
		int user_id;
		std::string user_state;
		std::string user_title;
		std::string username;
		std::string view_url;
		bool visible;
		int vote_score;
		int warning_points;
		std::string website;

	} User;
};

class CAuth
{
public:
	bool setup(std::string_view szEndpointUrl, std::string_view szApiKey);
	bool request(std::string_view szLogin, std::string_view szPassword);
	bool example();

	Auth_t Vars;

private:
	std::string m_szEndpointUrl;
	std::string m_szApiKey;
	cpr::Header m_cprHeader;
};

bool CAuth::setup(std::string_view szEndpointUrl, std::string_view szApiKey)
{
	if (szEndpointUrl.length() <= 1 || szApiKey.length() <= 1) /* checking input */
	{
		std::cout << "[CAuth::setup] Empty input." << std::endl;
		return false;
	}

	m_szEndpointUrl = szEndpointUrl;
	m_szApiKey = szApiKey;
	m_cprHeader = cpr::Header
	{
		{"Content-Type", "application/x-www-form-urlencoded"},
		{"XF-Api-Key", m_szApiKey},
		{"api_bypass_permissions", "1"}
	};

	return true;
}

bool CAuth::request(std::string_view szLogin, std::string_view szPassword)
{
	auto cprRequest = cpr::Post(cpr::Url{ m_szEndpointUrl }, cpr::Body{ fmt::format("login={}&password={}", szLogin, szPassword) }, m_cprHeader);
	//std::cout << cprRequest.text << std::endl;
	/* checking if the request takes five or more seconds */
	if (cprRequest.elapsed >= 5)
	{
		std::cout << "[cpr] Connection timeout." << std::endl;
		return false;
	}

	std::string szResponse = cprRequest.text;

	/* checking if we got a full json formatted reponse before parsing it */
	if (!nlohmann::json::accept(szResponse))
	{
		std::cout << "[json] Failed to accept response." << std::endl;
		return false;
	}

#ifdef _DEBUG
	std::cout << szResponse << std::endl;
#endif

	auto parsedResponse = nlohmann::json::parse(szResponse);

	/* checking if a error occured */
	if (parsedResponse.contains("errors"))
	{
		for (auto& errors : parsedResponse["errors"])
		{
			std::cout << "[forum] Error message: " << errors["message"] << std::endl; /* display the error message */
		}

		return false;
	}

	if (parsedResponse.contains("success"))
	{
		Vars.success = parsedResponse["success"];
	}

	if (!Vars.success)
	{
		std::cout << "[CAuth::request] Vars.success returned false." << std::endl;
		return false;
	}

	/* user field is missing, should not be triggered since we search for the error message first */
	if (!parsedResponse.contains("user"))
	{
		std::cout << "[CAuth::request] User field is missing." << std::endl;
		return false;
	}

	auto parsedUser = parsedResponse["user"];

	Vars.User.about = parsedUser["about"];
	Vars.User.activity_visible = parsedUser["activity_visible"];
	//	Vars.User.age = parsedUser["age"];
	Vars.User.alert_optout = parsedUser["alert_optout"].get<std::vector<int>>();
	Vars.User.allow_post_profile = parsedUser["allow_post_profile"];
	Vars.User.allow_receive_news_feed = parsedUser["allow_receive_news_feed"];
	Vars.User.allow_send_personal_conversation = parsedUser["allow_send_personal_conversation"];
	Vars.User.allow_view_identities = parsedUser["allow_view_identities"];
	Vars.User.allow_view_profile = parsedUser["allow_view_profile"];
	auto avatarUrls = parsedUser["avatar_urls"];
	Vars.User.avatar_urls.o = avatarUrls["o"].is_null() ? "unknown" : avatarUrls["o"];
	Vars.User.avatar_urls.h = avatarUrls["h"].is_null() ? "unknown" : avatarUrls["h"];
	Vars.User.avatar_urls.l = avatarUrls["l"].is_null() ? "unknown" : avatarUrls["l"];
	Vars.User.avatar_urls.m = avatarUrls["m"].is_null() ? "unknown" : avatarUrls["m"];
	Vars.User.avatar_urls.s = avatarUrls["s"].is_null() ? "unknown" : avatarUrls["s"];
	Vars.User.can_ban = parsedUser["can_ban"];
	Vars.User.can_converse = parsedUser["can_converse"];
	Vars.User.can_edit = parsedUser["can_edit"];
	Vars.User.can_follow = parsedUser["can_follow"];
	Vars.User.can_ignore = parsedUser["can_ignore"];
	Vars.User.can_post_profile = parsedUser["can_post_profile"];
	Vars.User.can_view_profile = parsedUser["can_view_profile"];
	Vars.User.can_view_profile_posts = parsedUser["can_view_profile_posts"];
	Vars.User.can_warn = parsedUser["can_warn"];
	Vars.User.content_show_signature = parsedUser["content_show_signature"];
	Vars.User.creation_watch_state = parsedUser["creation_watch_state"];
	auto customFields = parsedUser["custom_fields"];
	//Vars.User.custom_fields.skype = customFields["skype"].is_null() ? "unknown" : customFields["skype"];
	//Vars.User.custom_fields.facebook = customFields["facebook"].is_null() ? "unknown" : customFields["facebook"];
	//Vars.User.custom_fields.twitter = customFields["twitter"].is_null() ? "unknown" : customFields["twitter"];
	Vars.User.custom_title = parsedUser["custom_title"];
	/* object does not exist if dob is not saved in forum afaik. */
	/*if (parsedUser.contains("dob"))
	{
		auto dateOfBirth = parsedUser["dob"];
		Vars.User.dob.year = dateOfBirth["year"];
		Vars.User.dob.month = dateOfBirth["month"];
		Vars.User.dob.day = dateOfBirth["day"];
	}*/
	Vars.User.email = parsedUser["email"];
	Vars.User.email_on_conversation = parsedUser["email_on_conversation"];
	Vars.User.gravatar = parsedUser["gravatar"];
	Vars.User.interaction_watch_state = parsedUser["interaction_watch_state"];
	Vars.User.is_admin = parsedUser["is_admin"];
	/* for some reason the field disappeared in the response */
	if (parsedUser.contains("is_banned"))
	{
		Vars.User.is_banned = parsedUser["is_banned"];
	}
	Vars.User.is_discouraged = parsedUser["is_discouraged"];
	Vars.User.is_moderator = parsedUser["is_moderator"];
	Vars.User.is_staff = parsedUser["is_staff"];
	Vars.User.is_super_admin = parsedUser["is_super_admin"];
	Vars.User.last_activity = parsedUser["last_activity"];
	Vars.User.location = parsedUser["location"];
	Vars.User.message_count = parsedUser["message_count"];
	auto profileBannerUrls = parsedUser["profile_banner_urls"];
	Vars.User.profile_banner_urls.m = profileBannerUrls["m"].is_null() ? "unknown" : profileBannerUrls["m"];
	Vars.User.profile_banner_urls.l = profileBannerUrls["l"].is_null() ? "unknown" : profileBannerUrls["l"];
	Vars.User.push_on_conversation = parsedUser["push_on_conversation"];
	Vars.User.push_optout = parsedUser["push_optout"].get<std::vector<int>>();
	Vars.User.question_solution_count = parsedUser["question_solution_count"];
	Vars.User.reaction_score = parsedUser["reaction_score"];
	Vars.User.receive_admin_email = parsedUser["receive_admin_email"];
	Vars.User.register_date = parsedUser["register_date"];
	Vars.User.secondary_group_ids = parsedUser["secondary_group_ids"].get<std::vector<int>>();
	Vars.User.show_dob_date = parsedUser["show_dob_date"];
	Vars.User.show_dob_year = parsedUser["show_dob_year"];
	Vars.User.signature = parsedUser["signature"];
	Vars.User.timezone = parsedUser["timezone"];
	Vars.User.trophy_points = parsedUser["trophy_points"];
	Vars.User.usa_tfa = parsedUser["usa_tfa"];
	Vars.User.user_group_id = parsedUser["user_group_id"];
	Vars.User.user_id = parsedUser["user_id"];
	Vars.User.user_state = parsedUser["user_state"];
	Vars.User.user_title = parsedUser["user_title"];
	Vars.User.username = parsedUser["username"];
	Vars.User.view_url = parsedUser["view_url"];
	Vars.User.visible = parsedUser["visible"];
	Vars.User.vote_score = parsedUser["vote_score"];
	/* same here */
	if (parsedUser.contains("warning_points"))
	{
		Vars.User.warning_points = parsedUser["warning_points"];
	}
	Vars.User.website = parsedUser["website"];

	return true;
}

bool CAuth::example()
{
	/* check if user is banned */
	if (Vars.User.is_banned)
	{
		MessageBox(NULL, ("you're banned лох ебаный"), "amph.su", MB_ICONERROR | MB_DEFBUTTON2);
		exit(-1);
		//std::cout << "[CAuth::example] User banned." << std::endl;
		return false;
	}

	/* check if user has the allowed secondary group id */
	if (std::find(Vars.User.secondary_group_ids.begin(), Vars.User.secondary_group_ids.end(), 9) != Vars.User.secondary_group_ids.end()

		)
	{
		return true;
	}
	else {
		MessageBox(NULL, ("Subscription ERROR"), "amph.su", MB_ICONERROR | MB_DEFBUTTON2);
		exit(-1);
	}

	/* check if user is a staff member */

	/*if (Vars.User.is_admin || Vars.User.is_super_admin || Vars.User.is_moderator || Vars.User.is_staff)
	{
		return true;
	}*/




	return false;
}


