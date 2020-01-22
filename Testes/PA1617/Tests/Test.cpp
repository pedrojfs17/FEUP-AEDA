#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Mail.h"
#include "Postman.h"
#include "PostOffice.h"
#include <vector>
#include <string>
using namespace std;

TEST(test_1, a) {
	vector<int> v1;
	v1.push_back(10); v1.push_back(8);
	v1.push_back(12); v1.push_back(8);
	EXPECT_EQ(3, numberDifferent(v1));
	vector<string> v2;
	v2.push_back("ola"); v2.push_back("ola");
	EXPECT_EQ(1, numberDifferent(v2));
	v2.push_back("rio"); v2.push_back("arvore");
	v2.push_back("sol"); v2.push_back("sol");
	EXPECT_EQ(4, numberDifferent(v2));
}

TEST(test_1, b) {
	PostOffice po;
	Postman p1;
	p1. setName("joao");
	p1.addMail(new RegularMail("ana", "rui","4400-146", 33));
	p1.addMail(new RegularMail("luis", "rui","4400-146", 33));
	Postman p2;
	p2. setName("paulo");
	p2.addMail(new RegularMail("rui", "ana","3330-454", 33));
	p2.addMail(new RegularMail("luis", "maria","8600-306", 67));
	p2.addMail(new RegularMail("carla", "lara","7100-514", 67));
	Postman p3;
	p3.setName("fernando");
	p3.addMail(new RegularMail("manuel", "ana","3330-454", 33));
	po.addPostman(p1);
	po.addPostman(p2);
	po.addPostman(p3);

	vector <Mail *> mailP = po.removePostman("paulo");
	EXPECT_EQ(3, mailP.size());
	EXPECT_EQ(2,po.getPostman().size());

	mailP.clear();
	mailP = po.removePostman("sergio");
	EXPECT_EQ(0, mailP.size());

	mailP.clear();
	mailP = po.removePostman("fernando");
	EXPECT_EQ(1, mailP.size());

	mailP.clear();
	mailP = po.removePostman("joao");
	EXPECT_EQ(2, mailP.size());

	EXPECT_EQ(0,po.getPostman().size());
}

TEST(test_1, c) {
	RegularMail m1("manuel", "ana","3330-454", 33);
	RegularMail m2("ana", "rui","4400-146", 550);
	GreenMail m3("maria", "luis","2520-110", "bag");
	GreenMail m4("carla", "lara","7100-514", "envelope");

	EXPECT_EQ(75, m1.getPrice());
	EXPECT_EQ(325, m2.getPrice());
	EXPECT_EQ(200, m3.getPrice());
	EXPECT_EQ(80, m4.getPrice());
}

TEST(test_1, d) {
	PostOffice po("3100-000", "4409-999");
	po.addMailToSend(new RegularMail("manuel", "ana","3330-454", 33));
	po.addMailToSend(new RegularMail("ana", "rui","4400-146", 550));
	po.addMailToSend(new GreenMail("maria", "luis","2520-110", "bag"));
	po.addMailToSend(new GreenMail("carla", "lara","7100-514", "envelope"));

	unsigned int bal = 0;
	vector<Mail *> mailToOtherPO = po.endOfDay(bal);
	EXPECT_EQ(680, bal);
	EXPECT_EQ(2,mailToOtherPO.size());
	EXPECT_EQ(2,po.getMailToDeliver().size());
	EXPECT_EQ(0,po.getMailToSend().size());

	PostOffice po2("3100-000", "4409-999");
	po2.addMailToSend(new RegularMail("rita", "joana","5200-514", 120));

	mailToOtherPO = po2.endOfDay(bal);
	EXPECT_EQ(140, bal);
	EXPECT_EQ(1,mailToOtherPO.size());
	EXPECT_EQ(0,po2.getMailToDeliver().size());
	EXPECT_EQ(0,po2.getMailToSend().size());
}

TEST(test_1, e) {
	Postman p1("joao");
	Postman p2("rui");
	Postman p3("paulo");

	EXPECT_EQ(1, p1.getID());
	EXPECT_EQ(2, p2.getID());
	EXPECT_EQ(3, p3.getID());
}

TEST(test_1, f) {
	Postman p1;
	p1. setName("joao");
	p1.addMail(new RegularMail("rui", "ana","3330-454", 33));
	p1.addMail(new RegularMail("ana", "rui","4400-146", 33));
	p1.addMail(new RegularMail("luis", "rui","4400-146", 33));

	Postman p2;
	p2. setName("paulo");
	p2.addMail(new RegularMail("rui", "ana","3330-454", 33));
	p2.addMail(new RegularMail("carla", "lara","7100-514", 67));
	p2.addMail(new RegularMail("luis", "maria","8600-306", 67));

	EXPECT_EQ(true, p1<p2);
	EXPECT_EQ(false, p2<p1);

	p1.addMail(new RegularMail("joana", "rui","4400-146", 33));
	p1.addMail(new RegularMail("rita", "joana","5200-514", 120));
	p1.addMail(new RegularMail("maria", "lara","7100-514", 67));

	p2.addMail(new RegularMail("maria", "lara","8600-306", 67));

	EXPECT_EQ(false, p1<p2);
	EXPECT_EQ(true, p2<p1);
}

TEST(test_1, g) {
	PostOffice po;
	Postman p1;
	p1. setName("joao");
	p1.addMail(new RegularMail("ana", "rui","4400-146", 33));
	p1.addMail(new RegularMail("luis", "rui","4400-146", 33));
	Postman p2;
	p2. setName("paulo");
	Postman p3;
	p3.setName("fernando");
	p3.addMail(new RegularMail("manuel", "ana","3330-454", 33));
	po.addPostman(p1);
	po.addPostman(p2);
	po.addPostman(p3);

	Postman px = po.addMailToPostman(new RegularMail("rui", "ana","3330-454", 33),"paulo");
	EXPECT_EQ(1,px.getMail().size());

	EXPECT_THROW(po.addMailToPostman(new RegularMail("rui", "ana","3330-454", 33),"luis"), NoPostmanException);

	try {
		px = po.addMailToPostman(new RegularMail("rui", "ana","3330-454", 33),"joao");
		EXPECT_EQ(3,px.getMail().size());
		px = po.addMailToPostman(new RegularMail("rui", "ana","3330-454", 33),"ricardo");
	}
	catch(NoPostmanException &e) {
		EXPECT_EQ("ricardo", e.getName());
	}

	px = po.addMailToPostman(new RegularMail("rui", "ana","3330-454", 33),"fernando");
	EXPECT_EQ(2,px.getMail().size());
}


