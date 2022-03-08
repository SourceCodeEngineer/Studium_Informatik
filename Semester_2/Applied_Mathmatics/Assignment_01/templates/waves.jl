using Plots

p = plot( 0:0.1:2π, sin, label="sine", title="Triad sound wave" )
plot!( 0:0.1:2π,  cos, label="cosine")

display(p)