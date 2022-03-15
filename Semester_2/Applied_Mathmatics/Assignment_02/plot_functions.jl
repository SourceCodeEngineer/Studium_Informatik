using Plots,Base

function plot_function(fct, x_min, x_max, step_size)
    # TODO 
    # Hint: map function could be useful
end

# Using the example plots here, plot all functions in a nice layout.
# Choose x-ranges properly.
# TODO
fct_1(x) = x^2 + x + 1
fct_1_str = "f(x) = x^2 + x + 1"
fig_1 = plot_function(fct_1, -6.0, 5.0, 0.01)

fct_2(x) = x^4 - 3*x^2 - 1
fct_2_str = "f(x) = x^4 - 3x^2 - 1"
fig_2 = plot_function(fct_2, -2.0, 2.0, 0.01)

plot(fig_1, fig_2, layout=2, title=[fct_1_str fct_2_str], 
     titlefont = font(8), legend=false)

