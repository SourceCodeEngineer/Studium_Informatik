using Plots,Base

function plot_function(fct, x_min, x_max, step_size)
    plot(x_min:step_size:x_max,fct)
end

# Using the example plots here, plot all functions in a nice layout.
# Choose x-ranges properly.

fct_a(x) = 3 * x^2 - x - 7
fct_a_str = "f(x) = 3 * x^2 - x - 7"
fig_a = plot_function(fct_a, -6.0, 6.0, 0.01)

fct_b(x) = (7/5) ^ x - 1/2 * x^3
fct_b_str = "f(x) = (7/5) ^ x - 1/2 * x^3"
fig_b = plot_function(fct_b, -6.0, 6.0, 0.01)

fct_c(x) = 3 * sin(x) + cos(10*x) * 1/3 * sin(x)
fct_c_str = "f(x) = 3*sin(x)+cos(10*x)*1/3*sin(x)"
fig_c = plot_function(fct_c, -6.0, 6.0, 0.01)

fct_d(x) = abs(abs(abs(abs(x) -1) -1) -1)
fct_d_str = "f(x) = abs(abs(abs(abs(x) -1) -1) -1)"
fig_d = plot_function(fct_d, -6.0, 6.0, 0.01)

fct_e(x) = 1 / x
fct_e_str = "f(x) = 1 / x"
fig_e = plot_function(fct_e, -6.0, 6.0, 0.01)

fct_f(x) = log(abs(x - 1))
fct_f_str = "f(x) = log(abs(x - 1))"
fig_f = plot_function(fct_f, -6.0, 6.0, 0.01)


plot(fig_a,fig_b,fig_c,fig_d,fig_e,fig_f, layout=6, title=[fct_a_str fct_b_str fct_c_str fct_d_str fct_e_str fct_f_str], 
     titlefont = font(8), legend=false)
