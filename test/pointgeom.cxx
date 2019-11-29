#include "pointgeom.hh"

#include <cppunit/CompilerOutputter.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

class PointGeomTest : public CppUnit::TestFixture {
  public:
    static CppUnit::TestSuite* suite() {
        CppUnit::TestSuite* suiteOfTests =
            new CppUnit::TestSuite("Point Geometry");

        suiteOfTests->addTest(new CppUnit::TestCaller<PointGeomTest>{
            "No intersection", &PointGeomTest::no_intersection});

        suiteOfTests->addTest(new CppUnit::TestCaller<PointGeomTest>{
            "Horizontally parallel", &PointGeomTest::horizontally_parallel});

        suiteOfTests->addTest(new CppUnit::TestCaller<PointGeomTest>{
            "Horizontal Intersection",
            &PointGeomTest::horizontal_intersection});

        suiteOfTests->addTest(new CppUnit::TestCaller<PointGeomTest>{
            "Two horizontal lines intersect",
            &PointGeomTest::two_horizontal_lines_intersect});

        suiteOfTests->addTest(new CppUnit::TestCaller<PointGeomTest>{
            "Vertically parallel", &PointGeomTest::vertically_parallel});

        suiteOfTests->addTest(new CppUnit::TestCaller<PointGeomTest>{
            "Vertical intersection", &PointGeomTest::vertical_intersection});

        suiteOfTests->addTest(new CppUnit::TestCaller<PointGeomTest>{
            "Vertical miss", &PointGeomTest::vertical_miss});
        suiteOfTests->addTest(new CppUnit::TestCaller<PointGeomTest>{
            "Two vertical lines intersect",
            &PointGeomTest::two_vertical_lines_intersect});

        return suiteOfTests;
    }

    void no_intersection() {
        Line line1{Point{1, 1}, Point{2, 2}};
        Line line2{Point{2, 3}, Point{4, 3}};

        CPPUNIT_ASSERT_EQUAL(false, intersect(line1, line2));
    }

    void horizontally_parallel() {
        Line line1{Point{1, 1}, Point{2, 1}};
        Line line2{Point{2, 3}, Point{4, 3}};

        CPPUNIT_ASSERT_EQUAL(false, intersect(line1, line2));
    }

    void horizontal_intersection() {
        Line line1{Point{1, 2}, Point{10, 2}};
        Line line2{Point{5, 4}, Point{9, 1}};

        CPPUNIT_ASSERT_EQUAL(true, intersect(line1, line2));
    }

    void two_horizontal_lines_intersect() {
        Line line1{Point{1, 2}, Point{10, 2}};
        Line line2{Point{10, 2}, Point{15, 2}};
        CPPUNIT_ASSERT_EQUAL(true, intersect(line1, line2));

        line1 = Line{Point{1, 2}, Point{10, 2}};
        line2 = Line{Point{0, 2}, Point{15, 2}};
        CPPUNIT_ASSERT_EQUAL(true, intersect(line1, line2));

        line1 = Line{Point{1, 2}, Point{10, 2}};
        line2 = Line{Point{0, 2}, Point{1, 2}};
        CPPUNIT_ASSERT_EQUAL(true, intersect(line1, line2));
    }

    void vertically_parallel() {
        Line line1{Point{5, 2}, Point{5, 10}};
        Line line2{Point{2, 2}, Point{2, 10}};

        CPPUNIT_ASSERT_EQUAL(false, intersect(line1, line2));
    }

    void vertical_intersection() {
        Line line1{Point{5, 2}, Point{5, 10}};
        Line line2{Point{2, 1}, Point{7, 10}};

        CPPUNIT_ASSERT_EQUAL(true, intersect(line1, line2));
    }

    void two_vertical_lines_intersect() {
        Line line1{Point{5, 2}, Point{5, 10}};
        Line line2{Point{5, 10}, Point{5, 11}};
        CPPUNIT_ASSERT_EQUAL(true, intersect(line1, line2));

        line1 = Line{Point{5, 2}, Point{5, 10}};
        line2 = Line{Point{5, 0}, Point{5, 2}};
        CPPUNIT_ASSERT_EQUAL(true, intersect(line1, line2));

        line1 = Line{Point{5, 2}, Point{5, 10}};
        line2 = Line{Point{5, 0}, Point{5, 11}};
        CPPUNIT_ASSERT_EQUAL(true, intersect(line1, line2));

        line1 = Line{Point{5, 0}, Point{5, 11}};
        line2 = Line{Point{5, 0}, Point{5, 11}};
        CPPUNIT_ASSERT_EQUAL(true, intersect(line1, line2));
    }

    void vertical_miss() {
        Line line1{Point{5, 10}, Point{5, 20}};
        Line line2{Point{4, 9}, Point{5, 0}};

        CPPUNIT_ASSERT_EQUAL(false, intersect(line1, line2));
    }
};

int main() {
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(PointGeomTest::suite());
    return runner.run() ? 0 : 1;
}
