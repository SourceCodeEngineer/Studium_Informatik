using Plots

p = plot( 0:0.01:π, sin, label="sine", title="Triade sound wave")
plot!( 0:0.01:2π,  cos, label="cosine")

display(p)
