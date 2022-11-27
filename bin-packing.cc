/* Copyright (c) XNSC 2022
   This code is licensed under the MIT license (see LICENSE for details)

   Simple interactive CLI demonstrating the bin packing problem. This
   implementation runs in O(n!) time. */

#include <algorithm>
#include <iostream>
#include <vector>

static std::vector <unsigned int>
get_bins (void)
{
  std::vector <unsigned int> bins;
  while (1)
    {
      unsigned int size;
      std::cout << "Enter size of next bin (0 to finish): " << std::flush;
      std::cin >> size;
      if (!size)
	break;
      bins.push_back (size);
    }
  return bins;
}

static std::vector <std::pair <unsigned int, std::string>>
get_items (void)
{
  std::vector <std::pair <unsigned int, std::string>> items;
  while (1)
    {
      unsigned int value;
      std::string name;
      std::cout << "Enter value of next item (0 to finish): " << std::flush;
      std::cin >> value;
      if (!value)
	break;
      std::cout << "Enter name of next item: " << std::flush;
      std::cin.ignore ();
      std::getline (std::cin, name);
      items.push_back (std::make_pair (value, name));
    }
  return items;
}

static bool
get_allow_extra (void)
{
  char c;
  std::cout << "Consider arrangements requiring more than the specified "
    "number of bins? (y/n) " << std::flush;
  std::cin >> c;
  return c == 'y' || c == 'Y';
}

static bool
get_score (const std::vector <unsigned int> &bins,
	   const std::vector <std::pair <unsigned int, std::string>> &order,
	   unsigned int &score, unsigned int &left, bool allow_extra)
{
  unsigned int curr = 0;
  auto bin = bins.begin ();
  auto item = order.begin ();
  score = 0;
  while (item != order.end ())
    {
      if (bin == bins.end () || item->first > *bin)
	{
	  if (allow_extra)
	    {
	      score += item->first;
	      item++;
	    }
	  else
	    return false;
	}
      else if (curr + item->first > *bin)
	{
	  score += *bin - curr;
	  bin++;
	  curr = 0;
	}
      else
	{
	  curr += item->first;
	  item++;
	}
    }
  left = 0;
  while (bin != bins.end ())
    {
      left += *bin - curr;
      curr = 0;
      bin++;
    }
  return true;
}

int
main (void)
{
  std::vector <unsigned int> bins = get_bins ();
  std::vector <std::pair <unsigned int, std::string>> items = get_items ();
  bool allow_extra = get_allow_extra ();
  std::sort (items.begin (), items.end ());
  std::vector <std::pair <unsigned int, std::string>> best;
  unsigned int best_score = UINT_MAX;
  unsigned int best_left;
  do
    {
      unsigned int score;
      unsigned int left;
      if (get_score (bins, items, score, left, allow_extra)
	  && score < best_score)
	{
	  best = items;
	  best_score = score;
	  best_left = left;
	}
    }
  while (std::next_permutation (items.begin (), items.end ()));
  if (best_score == UINT_MAX)
    std::cout << "\nNo arrangement satisfies requirements given number of bins"
	      << std::endl;
  else
    {
      unsigned int curr = 0;
      unsigned int i = 1;
      auto bin = bins.begin ();
      std::cout << "\nFound best arrangement! Wasted+unfit space: "
		<< best_score << ", extra space: " << best_left << std::endl;
      std::vector <std::pair <unsigned int, std::string>> extras;
      unsigned int extras_sum = 0;
      auto item = best.begin ();
      while (item != best.end ())
	{
	  if (bin == bins.end () || item->first > *bin)
	    {
	      extras.push_back (*item);
	      extras_sum += item->first;
	      item++;
	    }
	  else if (curr + item->first > *bin)
	    {
	      bin++;
	      i++;
	      curr = 0;
	    }
	  else
	    {
	      if (!curr)
		std::cout << "\n=== BIN " << i << " (" << *bin << ") ==="
			  << std::endl;
	      curr += item->first;
	      std::cout << item->second << " (" << item->first << ")"
			<< std::endl;
	      item++;
	    }
	}
      if (!extras.empty ())
	{
	  std::cout << "\n=== EXTRAS (" << extras_sum << ") ===" << std::endl;
	  for (const auto &item : extras)
	    std::cout << item.second << " (" << item.first << ")" << std::endl;
	}
    }
  return 0;
}
