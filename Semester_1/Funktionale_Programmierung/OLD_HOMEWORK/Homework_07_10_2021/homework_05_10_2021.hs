-- Define a function milesToKilometers m = ... to convert miles into kilometers.
milesToKilometers m = m * 1.60934

--Define a function volume r = ... to compute the volume of a sphere with radius r.
volume r = (4/3) * 3.1415 * r * r * r

--Define a function average x y = ... that computes the average of two numbers x and y.
average x y = (x + y) / 2

--Is average (average x y) z the average of three numbers x, y and z?
-- No, because we calculate the average of x and y first and then we calculate with the return value of "average x y" and z
--which is not correct!

--Define a function averageVolume r1 r2 = ... that computes the average volume of two spheres having
--radius r1 and r2, respectively.
averageVolume r1 r2 = ((volume r1) + (volume r2)) / 2