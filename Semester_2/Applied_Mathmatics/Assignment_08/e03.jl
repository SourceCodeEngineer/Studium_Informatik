using Plots

module HeatEquationSolver
function initializeXs(border_l::Float64, border_r::Float64, N_grid_points::Int)::Tuple{Float64, Vector}
    # Setup range for space grid
    xs = range(border_l, length=N_grid_points+1, stop=border_r)
    # Get step size for space grid.
    h = step(xs)
    h, xs
end

function initializeUs(xs::Vector, f_init::Function, boundary_l::Float64, boundary_r::Float64)::Vector
    # Initialize u values at space grid points for time step 0.
    us_init = f_init.(xs)

    # Set boundary conditions.
    us_init[1] = boundary_l
    us_init[end] = boundary_r
    us_init
end

function explicitStep(us::Vector, h::Float64, tau::Float64)::Vector
    result_vector = zeros(Float64, length(us))
    #Ersten und letzten Wert eintragen, damit es beim Iterieren nicht zu einem Fehler kommt.
    #-> (wegen [i-1] und [i+1])
    result_vector[1] = us[1]
    result_vector[length(result_vector)] = us[length(us)]

    #für jeden Zeitschritt einmal durchführen, bei 2 beginnen, da [1] schon gesetzt.
    for i in 2:(length(us)-1)
        result_vector[i] = us[i] + tau * (us[i+1] - 2 * us[i] + us[i-1]) / h ^ 2 
    end
    result_vector
end

function solveOverTime(border_l::Float64, border_r::Float64, N_grid_points::Int, f_init::Function, boundary_l::Float64, boundary_r::Float64, N_time_steps::Int, tau::Float64)::Tuple{Vector, Vector, Array}
    # initialize space grid points
    h, xs = initializeXs(border_l, border_r, N_grid_points)

    ts = range(0.0, length=N_time_steps+1, step=tau)

    # Initialize u values on space grid points for time step 0.
    us_init = initializeUs(xs, f_init, boundary_l, boundary_r)

    # Initialize array to store u values over time.
    us_over_time = zeros(Float64, (length(us_init), N_time_steps+1))

    # Add initial us to array.
    us_over_time[:, 1] = us_init

    # Iterate over time steps and perform explicit update steps. Store the resulting us in array.
    for t in 1:N_time_steps
        # ts[t+1] = t * tau
        us_over_time[:, t+1] = explicitStep(us_over_time[:, t], h, tau)
    end

    # Return x grid points, t grid points and us over time.
    xs, ts, us_over_time
end
end

function plotOverTime(border_l::Float64, border_r::Float64, N_grid_points::Int, f_init::Function, boundary_l::Float64, boundary_r::Float64, N_time_steps::Int, tau::Float64)
    xs, ts, us_over_time = HeatEquationSolver.solveOverTime(border_l, border_r, N_grid_points, f_init, boundary_l, boundary_r, N_time_steps, tau)
    plt_1D = plot(xs, us_over_time[:, 1], legend=true, xlabel="x", ylabel="u(x, t)", linewidth=3, color=:blue, label="t=" * string(ts[1]))

    for t in 2:10:(N_time_steps+1)
        plot!(plt_1D, xs, us_over_time[:, t], color=:red, label="")
    end
    plot!(plt_1D, xs, us_over_time[:, end], linewidth=3, label="t=" * string(ts[end]))

    plt_2D = heatmap(ts, xs, us_over_time, xlabel="t", ylabel="x", colorbar_title="u(x, t)")
    plt_1D, plt_2D
end

u_init(x) = exp(-x)

border_l = -1.0
border_r = 1.0
boundary = Float64(π)

N_grid_points = 40
tau = 0.001
N_time_steps = 1000

plt_1D, plt_2D = plotOverTime(border_l, border_r, N_grid_points, u_init, boundary, boundary, N_time_steps, tau)
p = plot(
    plt_1D,
    plt_2D,
    layout=(2, 1)
)
plot!(size=(1200, 960))
