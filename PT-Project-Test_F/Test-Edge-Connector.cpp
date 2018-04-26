#include"../PT-Project/Statements/Connector.h"
#include"../PT-Project/Statements/ReadWrite.h"
#include"../PT-Project/Statements/Conditional.h"

#include<gtest\gtest.h>

TEST(ConnectorEdgeCoverage,Constructor) {
	ReadWrite * Src = new ReadWrite();
	ReadWrite * Dst = new ReadWrite();

	Connector *x = new Connector(Src,Dst,false);
	EXPECT_EQ(x->getSrcStat(), Src);
	EXPECT_EQ(x->getDstStat(), Dst);
	EXPECT_EQ(x->getEndPoint().x, Dst->getIn().x);
	EXPECT_EQ(x->getEndPoint().y, Dst->getIn().y);
	EXPECT_EQ(x->Selected, false);
	EXPECT_EQ(x->def, 0);

	Point * parr;
	int s;
	Src->getOut(parr,s);
	EXPECT_EQ(x->getStartPoint().x, parr[0].x);
	EXPECT_EQ(x->getStartPoint().y, parr[0].y);

	Conditional *Src2 = new Conditional(Point(50,50), "X", ">", 2, "", 1);
	x = new Connector(Src2, Dst, false);

	EXPECT_EQ(x->getSrcStat(), Src2);
	EXPECT_EQ(x->getDstStat(), Dst);
	EXPECT_EQ(x->getEndPoint().x, Dst->getIn().x);
	EXPECT_EQ(x->getEndPoint().y, Dst->getIn().y);
	EXPECT_EQ(x->Selected, false);
	EXPECT_EQ(x->def, 0);

	Src2->getOut(parr, s);
	EXPECT_EQ(x->getStartPoint().x,parr[0].x);
	EXPECT_EQ(x->getStartPoint().y, parr[0].y);

	Src2 = new Conditional(Point(50, 50), "X", ">", 2, "", 1);
	Src2->setConn(new Connector(Src,Dst,false));
	x = new Connector(Src2, Dst, false);

	EXPECT_EQ(x->getSrcStat(), Src2);
	EXPECT_EQ(x->getDstStat(), Dst);
	EXPECT_EQ(x->getEndPoint().x, Dst->getIn().x);
	EXPECT_EQ(x->getEndPoint().y, Dst->getIn().y);
	EXPECT_EQ(x->Selected, false);
	EXPECT_EQ(x->def, 1);

	Src2->getOut(parr, s);
	EXPECT_EQ(x->getStartPoint().x, parr[1].x);
	EXPECT_EQ(x->getStartPoint().y, parr[1].y);

}

TEST(ConnectorEdgeCoverage, SettersAndGetters) {
	ReadWrite * Src = new ReadWrite();
	ReadWrite * Dst = new ReadWrite();

	Connector *x = new Connector(Src, Dst, false);
	
	x->setSrcStat(Dst);
	EXPECT_EQ(x->getSrcStat(),Dst);
	EXPECT_EQ(x->SrcStat, Dst);

	x->setDstStat(Src);
	EXPECT_EQ(x->getDstStat(), Src);
	EXPECT_EQ(x->DstStat, Src);

	x->setStartPoint(Point(50, 50));
	EXPECT_EQ(x->getStartPoint(),Point(50,50));
	EXPECT_EQ(x->Start, Point(50, 50));

	x->setEndPoint(Point(50, 50));
	EXPECT_EQ(x->getEndPoint(), Point(50, 50));
	EXPECT_EQ(x->End, Point(50, 50));
}

TEST(ConnectorEdgeCoverage,Save ) {
	ReadWrite * Src = new ReadWrite();
	ReadWrite * Dst = new ReadWrite();

	Connector *x = new Connector(Src, Dst, false);
	
	ofstream o("conn.save.test");
	x->Save(o);
	o.close();

	ifstream file("conn.save.test");
	int i;
	file >> i;
	EXPECT_EQ(i,Src->getID());

	file >> i;
	EXPECT_EQ(i, Dst->getID());

	file >> i;
	EXPECT_EQ(i,0);
	file.close();


	o.open("conn.save.test");
	Conditional *Src2 = new Conditional(Point(50, 50), "X", ">", 2, "", 1);
	x = new Connector(Src2, Dst, false);
	x->Save(o);
	o.close();

	file.open("conn.save.test");
	file >> i;
	EXPECT_EQ(i, Src2->getID());

	file >> i;
	EXPECT_EQ(i, Dst->getID());

	file >> i;
	EXPECT_EQ(i, 1);
	file.close();



	o.open("conn.save.test");
	Conditional *Src3 = new Conditional(Point(50, 50), "X", ">", 2, "", 1);
	Src3->setConn(new Connector(Src,Dst,true));
	x = new Connector(Src3, Dst, false);
	x->Save(o);
	o.close();

	file.open("conn.save.test");
	file >> i;
	EXPECT_EQ(i, Src3->getID());

	file >> i;
	EXPECT_EQ(i, Dst->getID());

	file >> i;
	EXPECT_EQ(i, 2);
	file.close();
}