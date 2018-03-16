\ENCODING=ISO-8859-1
\Problem name: IloCplex

Minimize
 obj: - 9355 passengers(0) - 5525.34 passengers(1) - 4175 passengers(2)
      - 9525 passengers(3) - 8752.5 passengers(4) - 5821.66 passengers(5)
      - 5099 passengers(6) - 5303 passengers(7) - 7001.34 passengers(8)
      - 5494.34 passengers(9) - 5504.66 passengers(10) - 5136 passengers(11)
      - 7212.16 passengers(12) - 992 passengers(13) - 4870 passengers(14)
      - 6544 passengers(15) - 5448.34 passengers(16) - 7480.84 passengers(17)
      - 6641.34 passengers(18) - 4459.5 passengers(19) + x41
      + [ 2 passengers(0) ^2 + 2 passengers(1) ^2 + 2 passengers(2) ^2
      + 2 passengers(3) ^2 + 2 passengers(4) ^2 + 2 passengers(5) ^2
      + 2 passengers(6) ^2 + 2 passengers(7) ^2 + 2 passengers(8) ^2
      + 2 passengers(9) ^2 + 2 passengers(10) ^2 + 2 passengers(11) ^2
      + 2 passengers(12) ^2 + 2 passengers(13) ^2 + 2 passengers(14) ^2
      + 2 passengers(15) ^2 + 2 passengers(16) ^2 + 2 passengers(17) ^2
      + 2 passengers(18) ^2 + 2 passengers(19) ^2 ] / 2
Subject To
 ODPassengers(0):  passengers(0) - OD(0)(2) - 0.5 OD(0)(3) - 0.25 OD(0)(4)
                   - 0.333333 OD(2)(4) - OD(3)(1)  = 0
 ODPassengers(1):  passengers(1) - OD(0)(1) - 0.25 OD(3)(2) - 0.333333 OD(4)(2)
                    = 0
 ODPassengers(2):  - 0.5 OD(0)(3) - 0.333333 OD(2)(4) + passengers(2)
                   - 0.5 OD(1)(3)  = 0
 ODPassengers(3):  - 0.75 OD(0)(4) + passengers(3) - OD(1)(2)
                   - 0.666666 OD(1)(4) - OD(3)(4)  = 0
 ODPassengers(4):  - 0.25 OD(3)(2) - 0.5 OD(1)(3) - OD(1)(2)
                   - 0.333333 OD(1)(4) + passengers(4) - 0.333333 OD(1)(0)
                   - 0.333333 OD(2)(0) - 0.25 OD(4)(0)  = 0
 ODPassengers(5):  - 0.25 OD(0)(4) - 0.333333 OD(4)(2) - 0.333333 OD(1)(4)
                   - 0.666666 OD(1)(0) + passengers(5)  = 0
 ODPassengers(6):  - OD(0)(2) - 0.333333 OD(2)(4) + passengers(6)
                   - 0.25 OD(2)(3)  = 0
 ODPassengers(7):  - 0.5 OD(0)(3) - 0.333333 OD(2)(4) - 0.5 OD(1)(3)
                   - 0.333333 OD(1)(4) + passengers(7)  = 0
 ODPassengers(8):  - 0.666666 OD(2)(4) - 0.333333 OD(1)(4) - 0.333333 OD(1)(0)
                   - 0.666667 OD(2)(0) + passengers(8)  = 0
 ODPassengers(9):  - 0.333333 OD(2)(4) - 0.333333 OD(2)(0) - 0.25 OD(2)(3)
                   + passengers(9) - OD(2)(1)  = 0
 ODPassengers(10): - 0.333333 OD(1)(0) - 0.5 OD(2)(3) + passengers(10)
                   - OD(4)(3)  = 0
 ODPassengers(11): - 0.25 OD(0)(4) - OD(0)(1) - 0.25 OD(2)(3) + passengers(11)
                    = 0
 ODPassengers(12): - OD(3)(4) - 0.333333 OD(1)(0) - 0.25 OD(4)(0)
                   + passengers(12) - OD(3)(0)  = 0
 ODPassengers(13): - 0.25 OD(3)(2) + passengers(13)  = 0
 ODPassengers(14): - OD(0)(2) - 0.5 OD(3)(2) + passengers(14)  = 0
 ODPassengers(15): - 0.666666 OD(2)(4) - OD(3)(1) - 0.25 OD(3)(2)
                   + passengers(15)  = 0
 ODPassengers(16): - OD(3)(1) - 0.333333 OD(4)(2) - 0.5 OD(4)(0)
                   + passengers(16)  = 0
 ODPassengers(17): - OD(0)(1) - 0.333333 OD(4)(2) - 0.25 OD(4)(0)
                   + passengers(17) - OD(4)(1)  = 0
 ODPassengers(18): - 0.25 OD(3)(2) - 0.333333 OD(4)(2) - OD(1)(2) - OD(4)(3)
                   + passengers(18)  = 0
 ODPassengers(19): - 0.5 OD(0)(3) - 0.5 OD(1)(3) - 0.25 OD(4)(0)
                   - 0.25 OD(2)(3) + passengers(19)  = 0
Bounds
 2338 <= passengers(0) <= 9355
 1381 <= passengers(1) <= 5525
 1043 <= passengers(2) <= 4175
 2381 <= passengers(3) <= 9525
 2188 <= passengers(4) <= 8752
 1455 <= passengers(5) <= 5821
 1274 <= passengers(6) <= 5099
 1325 <= passengers(7) <= 5303
 1750 <= passengers(8) <= 7001
 1373 <= passengers(9) <= 5494
 1376 <= passengers(10) <= 5504
 1284 <= passengers(11) <= 5136
 1803 <= passengers(12) <= 7212
 248 <= passengers(13) <= 992
 1217 <= passengers(14) <= 4870
 1636 <= passengers(15) <= 6544
 1362 <= passengers(16) <= 5448
 1870 <= passengers(17) <= 7480
 1660 <= passengers(18) <= 6641
 1114 <= passengers(19) <= 4459
      x41 = 198972406.2601
End
