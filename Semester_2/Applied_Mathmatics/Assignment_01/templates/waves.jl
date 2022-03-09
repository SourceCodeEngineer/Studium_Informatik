using Plots

amplitude = 1

frequenz_E = 329.63
frequenz_G_SHARP = 415.30
frequenz_B = 493.88

k(t) = amplitude  * sin(2 * pi * frequenz_E * t)
l(t) = amplitude  * sin(2 * pi * frequenz_G_SHARP * t)
m(t) = amplitude  * sin(2 * pi * frequenz_B * t)
n(t) = k(t) + l(t) + m(t) 

p = plot(0:0.00001:0.01, k , label="E = 329.63 Hz", title="Triade sound wave", xlabel="t (seconds)", ylabel="y(t)")
plot!(0:0.00001:0.01,  l , label="G# = 415.30 Hz")
plot!(0:0.00001:0.01, m , label="B = 493.88 Hz")
plot!(0:0.00001:0.01, n , label="triad")
display(p)
