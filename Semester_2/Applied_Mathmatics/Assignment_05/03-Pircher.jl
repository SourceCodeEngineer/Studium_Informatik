using Plots

# differential equations
x_dd(t) = 0
y_dd(t) = -g

# analytic solution
x(t, θ, h_0, v) = v * cos(θ) * t
y(t, θ, h_0, v) = h_0 + t * v * sin(θ) - g * t^2 / 2

# optimal angle for maximum distance l
Theta(h_0, v) = asin(v / √(2 * g * h_0 + 2 * v^2))
# time until height = 0
T(θ, h_0, v) = (v * sin(θ) + √((v * sin(θ))^2 + 2 * g * h_0)) / g

# parameters
g = 9.81 # m/s^2 gravity
v = 20.0 # m/s speed
h_0 = 15.0 # m initial height
θ = Theta(h_0, v) # angle to achieve maximum distance l 


function solve_ex_euler(θ::Float64, h_0::Float64, v::Float64, time::Float64, h::Float64)
    # initial position
    x_n = zeros(length(0:h:time))
    y_n = zeros(length(0:h:time))

    x_d_n = zeros(length(0:h:time))
    y_d_n = zeros(length(0:h:time))

    error_x = zeros(length(0:h:time))
    error_y = zeros(length(0:h:time))

    # initial position
    x_n[1] = 0.0
    y_n[1] = h_0

    # initial velocity
    x_d_n[1] = v * cos(θ)
    y_d_n[1] = v * sin(θ)

    for (i, t) in enumerate(h:h:time)
        #========== 3b: solve differential equations numerically =========#
        # add the computed values to the corresponding array
        # for example:
        # horizontal distance at t_0 -> x_n[1]
        # vertical velocity at t_2 -> y_d_n[3]
        x_d_n[i+1] = x_d_n[i] + h * x_dd(t)
        y_d_n[i+1] = y_d_n[i] + h * y_dd(t)

        x_n[i+1] = x_n[i] + h * x_d_n[i]
        y_n[i+1] = y_n[i] + h * y_d_n[i]

        error_x[i+1] = abs(x(t, θ, h_0, v) - x_n[i+1])
        error_y[i+1] = abs(y(t, θ, h_0, v) - y_n[i+1])
    end

    x_n, y_n, error_x, error_y
end

# explicit euler timestep
h = 0.25
max_time = T(θ, h_0, v)

# solve with explicit euler
distance, height, error_x, error_y = solve_ex_euler(θ, h_0, v, max_time, h)

# plot numeric solution
plot_curve = plot(distance, height, label="numeric h=" * string(h), legend=:bottomleft, color="red", xlabel="distance", ylabel="height", ylims=(0.0, Inf), margin=6Plots.mm)

# plot analytic solution
time = 0:0.01:max_time
plot!(plot_curve, (t -> x(t, θ, h_0, v)).(time), (t -> y(t, θ, h_0, v)).(time), label="analytic", color="blue")

# plot error
time = 0:h:max_time
plot_error = plot(time, [error_x, error_y], labels=["distance" "height"], legend=:topleft, xlabel="time(s)", ylabel="error")

plot_combined = plot(plot_curve, plot_error, layout=(1, 2), size=(1280, 720))
display(plot_combined)
