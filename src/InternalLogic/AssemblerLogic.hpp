#pragma once

#define Add add

template <typename LeftType, typename RightType>
LeftType &add(LeftType &left, RightType &right)
{
    left.add(right);
    return left;
}
