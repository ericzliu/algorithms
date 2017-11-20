#include "stdafx.h"
#include "CppUnitTest.h"
#include "app.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestPower)
		{
			// TODO: Your test code here
         auto p = upow(2, 3);
         Assert::AreEqual(8u, p);
         p = upow(2, 5);
         Assert::AreEqual(32u, p);
		}

      TEST_METHOD(TestCombSize)
      {
         auto s = comb_size(1u);
         Assert::AreEqual(1u, s);
         s = comb_size(2u);
         Assert::AreEqual(1u, s);
         s = comb_size(5u);
         Assert::AreEqual(2u, s);
         s = comb_size(0u);
         Assert::AreEqual(0u, s);
      }

      TEST_METHOD(TestCombIterator)
      {
         comb_iterator jiterator(2, 0u);
         Assert::AreEqual(false, jiterator.has_next());
         jiterator = comb_iterator(2, 1u);
         Assert::AreEqual(true, jiterator.has_next());
         auto loc = jiterator.next();
         Assert::AreEqual(false, jiterator.has_next());
         Assert::AreEqual(0u, loc);
         jiterator = comb_iterator(4, 6u);
         jiterator.has_next();
         Assert::AreEqual(1u, jiterator.next());
         jiterator.has_next();
         Assert::AreEqual(2u, jiterator.next());
         Assert::AreEqual(false, jiterator.has_next());
         jiterator = comb_iterator(2, 3u);
         jiterator.has_next();
         Assert::AreEqual(0u, jiterator.next());
         jiterator.has_next();
         Assert::AreEqual(1u, jiterator.next());

         jiterator = comb_iterator(2, 7u);
         jiterator.has_next();
         Assert::AreEqual(0u, jiterator.next());
         jiterator.has_next();
         Assert::AreEqual(1u, jiterator.next());
         Assert::AreEqual(false, jiterator.has_next());
      }

      TEST_METHOD(TestCombRemove)
      {
         unsigned comb = 0u;
         auto n = comb_remove(comb, 0u);
         Assert::AreEqual(0u, comb);
         Assert::AreEqual(0u, n);
         comb = 1u;
         n = comb_remove(comb, 0u);
         Assert::AreEqual(0u, n);
         Assert::AreEqual(1u, comb);
         comb = 5u;
         n = comb_remove(comb, 2u);
         Assert::AreEqual(1u, n);
         Assert::AreEqual(5u, comb);
      }

      TEST_METHOD(TestCombTest)
      {
         unsigned comb = 0u;
         Assert::AreEqual(false, comb_test(comb, 0u));
         Assert::AreEqual(false, comb_test(comb, 1u));
         comb = 1u;
         Assert::AreEqual(true, comb_test(comb, 0u));
         Assert::AreEqual(false, comb_test(comb, 1u));
         comb = 5u;
         Assert::AreEqual(true, comb_test(comb, 0u));
         Assert::AreEqual(false, comb_test(comb, 1u));
         Assert::AreEqual(true, comb_test(comb, 2u));
      }

      TEST_METHOD(TestCombs)
      {
         combs unit_combs(1);
         auto subsets = &unit_combs.get_combs(0);
         Assert::AreEqual(1u, subsets->size());
         subsets = &unit_combs.get_combs(1);
         Assert::AreEqual(1u, subsets->size());

         combs tri_combs(3);
         subsets = &tri_combs.get_combs(0);
         Assert::AreEqual(1u, subsets->size());
         Assert::AreEqual(0u, subsets->at(0));
         subsets = &tri_combs.get_combs(1);
         Assert::AreEqual(3u, subsets->size());
         Assert::AreEqual(1u, subsets->at(0));
         Assert::AreEqual(2u, subsets->at(1));
         Assert::AreEqual(4u, subsets->at(2));
         subsets = &tri_combs.get_combs(2);
         Assert::AreEqual(3u, subsets->size());
         Assert::AreEqual(3u, subsets->at(0));
         Assert::AreEqual(5u, subsets->at(1));
         Assert::AreEqual(6u, subsets->at(2));
         subsets = &tri_combs.get_combs(3);
         Assert::AreEqual(1u, subsets->size());
         Assert::AreEqual(7u, subsets->at(0));
      }

      TEST_METHOD(TestTspDp) {
         vector< node > empty_graph;
         double dist = tsp_dp(empty_graph);
         Assert::AreEqual(0.0, dist);

         vector< node > graph;
         graph.push_back(node(1, 1));
         dist = tsp_dp(graph);
         Assert::AreEqual(0.0, dist);

         graph.push_back(node(2, 1));
         dist = tsp_dp(graph);
         Assert::AreEqual(2.0, dist);

         graph.push_back(node(3, 1));
         dist = tsp_dp(graph);
         Assert::AreEqual(4.0, dist);

         vector< node > graph2;
         graph2.push_back(node(0, 0));
         graph2.push_back(node(1, 1));
         graph2.push_back(node(1, -1));
         graph2.push_back(node(2, 0));
         dist = tsp_dp(graph2);
         Assert::AreEqual(true, 5.66 > dist);
         Assert::AreEqual(true, 5.65 < dist);
      }
	};
}