#pragma once
#include <ctype.h>
#include <memory>
#include <boost/serialization/split_member.hpp>

#include "SHA25.h"
#include "KeyPair.h"
using std::string;

class Message
{
public:
	Message() : nom_de_domaine(), information(), hashDomainName(), publicKey(), longueurMessage(), signature() {

	};

	Message(string, string, const KeyPair&);
	~Message();

	string			getNomDomaine() const;
	string			getinformation() const;
	string			getHashDomainName() const;
	RSA::PublicKey  getPublicKey() const;

	bool		 verifier() const;
	SecByteBlock sign(RSA::PrivateKey&);


	template<class Archive>
	void save(Archive & ar, const unsigned int version) const
	{
		ar & nom_de_domaine & information & longueurMessage;
		string aa = boost::lexical_cast<std::string>(publicKey.GetPublicExponent());
		string bb = boost::lexical_cast<std::string>(publicKey.GetModulus());
		ar & aa & bb;
		//std::string token = std::string(reinterpret_cast<const char*>(signature.data()), signature.size()); TODO
		//std::cout << " " << token << std::endl;
		//ar & token;
	}

	template<class Archive>
	void load(Archive & ar, const unsigned int version)
	{

		string d, e, f;
		ar & nom_de_domaine & information & longueurMessage;
		ar & d & e;
		publicKey.SetPublicExponent(CryptoPP::Integer(d.c_str()));
		publicKey.SetModulus(CryptoPP::Integer(e.c_str()));
		// ar & f;
		//signature = SecByteBlock(reinterpret_cast<const byte*>(f.data()), f.size());
	}

	BOOST_SERIALIZATION_SPLIT_MEMBER()


private:
	std::string		 nom_de_domaine;	// TODO perhaps let const if serialization is ok with it
	std::string		 information;
	string			 hashDomainName;
	RSA::PublicKey   publicKey;
	__int64			 longueurMessage;
	SecByteBlock	 signature;


};

