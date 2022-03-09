using Plots

x = todo
y = todo
z = todo 
w = todo


p = plot( 0:0.005:0.01, sin, label="E = 329.63 Hz", title="Triade sound wave")
plot!( 0:0.005:0.001,  cos, label="G# = 415.30 Hz")
plot!( 0:0.005:0.001,  cos, label="B = 493.88 Hz")
plot!( 0:0.005:0.001,  cos, label="triad")
display(p)
