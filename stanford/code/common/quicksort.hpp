#pragma once

#include <vector>
#include <algorithm>

using std::vector;
using std::swap;

namespace alg
{

    template <typename T>
    size_t chooseLeft(vector<T> & vec, size_t left, size_t right)
    {
        return left;
    }

    template <typename T>
    size_t chooseRight(vector<T> & vec, size_t left, size_t right)
    {
        T pivot = vec[right];
//        swap(vec[right], vec[left]);
        return right;
    }

    template <typename T>
    size_t chooseMedianOfThree(vector<T> & vec, size_t left, size_t right)
    {
        T begin = vec[left];
        T end   = vec[right];
        size_t midIndex = vec.size()/2 - 1;
        T mid   = vec[midIndex];

        T median = max(min(begin,end), min(max(begin,end),mid));

//        // always place median as first value in array
        if (median == end)
        {
//            swap(vec[right], vec[left]);
            return right;
        }
        else if (median == mid)
        {
//            swap(vec[midIndex], vec[left]);
            return midIndex;
        }
        else
        {
            return left;
        }

//        return median;
    }

    template <typename T>
    size_t partition(
            vector<T> & vec,
            size_t left,
            size_t right,
            size_t (*choosePivotFunc)(vector<T>&, size_t, size_t) = &chooseLeft)
    {
        size_t pivotIndex = choosePivotFunc(vec, left, right);
        T pivot = vec[pivotIndex];
        swap(vec[left], vec[pivotIndex]);

        size_t border = left + 1;
        for (size_t j = left + 1; j <= right; ++j)
        {
            if (vec[j] < pivot)
            {
                swap(vec[border], vec[j]);
                ++border;
            }
        }
        swap(vec[left], vec[border - 1]);
        return border - 1;
    }

    template <typename T>
    size_t quicksort(
            vector<T> & vec,
            size_t left,
            size_t right,
            size_t (*choosePivotFunc)(vector<T>&, size_t, size_t) = &chooseLeft)
    {
        size_t vec_size = right - left + 1;
        if (vec_size < 2) return 0;

        size_t pivotIndex = partition(vec, left, right, choosePivotFunc);

        size_t numComp = (pivotIndex - 1) - left + 1;
        numComp += quicksort(vec, left, pivotIndex - 1, choosePivotFunc);

        numComp += right - (pivotIndex + 1) + 1;
        numComp += quicksort(vec, pivotIndex + 1, right, choosePivotFunc);

        return numComp;
    }

}
