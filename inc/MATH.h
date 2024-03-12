//
// Created by 86189 on 2024/1/30.
//

#ifndef DEMO_MATH_H
#define DEMO_MATH_H
#define YUN_D_MATH_LIMIT(MAX, MIN, DATA) ((DATA > MAX) ? MAX : ((DATA < MIN) ? MIN : DATA))
#define YUN_D_MATH_ABS(DATA) ((DATA) < 0 ? -(DATA) : (DATA))
#endif //DEMO_MATH_H
