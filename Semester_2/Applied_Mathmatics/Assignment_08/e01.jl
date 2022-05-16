using Plots
using Plots.PlotMeasures

module FiniteDiff

function forward(x::Float64, h::Float64, f::Function)::Float64
    (f(x+h) - f(x)) / h
end

function backward(x::Float64, h::Float64, f::Function)::Float64
    (f(x) - f(x-h)) / h
end

function central(x::Float64, h::Float64, f::Function)::Float64
    (f(x+h/2) - f(x-h/2)) / h
end
end

function f(x::Float64)::Float64
    tanh(x)
end

function f1(x::Float64)::Float64
    (4*exp(2*x)) / ((exp(2x)+1)^2)
end

function plotFunctionAndErrors(i_start::Float64, i_end::Float64, h::Float64, f::Function, f1::Function)
    X = i_start : ((i_end-i_start)/100) : i_end;
    Y = f.(X);

    Xds = i_start : 0.05 : i_end
    Yds = f1.(Xds);

    Xd = i_start : h : i_end
    Yd = f1.(Xd);
    Ydforw = FiniteDiff.forward.(Xd, h, f)
    Ydbackw = FiniteDiff.backward.(Xd, h, f)
    Ydcentr = FiniteDiff.central.(Xd, h, f)

    plt1 = plot(X, Y, color= :black, xlabel="x", ylabel="f(x)", title="f(x)", legend=false, left_margin=4mm, bottom_margin=3mm)

    plt2 = plot(Xds, Yds, color= :black, label="Analytical", xlabel="x", ylabel="f'(x)", title="f'(x), h=" * string(h), legend=:top, left_margin=4mm, bottom_margin=3mm)
    plot!(plt2, Xd, Ydforw, color= :grey, label="Forward")
    plot!(plt2, Xd, Ydbackw, color= :blue, label="Backward")
    plot!(plt2, Xd, Ydcentr, color= :red, label="Central")

    ErrF = abs.(Yd .- Ydforw);
    ErrB = abs.(Yd .- Ydbackw);
    ErrC = abs.(Yd .- Ydcentr);

    pltErr = plot(Xd, ErrF, color= :grey, label="Forward", xlabel="x", ylabel="error", title="Error to analytical solution, h=" * string(h), left_margin=4mm, bottom_margin=3mm)
    plot!(pltErr, Xd, ErrB, color= :blue, label="Backward")
    plot!(pltErr, Xd, ErrC, color= :red, label="Central")

    plot(plt1, plt2, pltErr, layout=(3,1))
end

function plotErrorVaryingH(x::Float64, N::Int, f::Function, f1::Function)
    target = f1(x)

    EFo = zeros(N)
    EBa = zeros(N)
    ECe = zeros(N)
    X = zeros(N)

    for i = 1:N
        h = 1.0/Float64(i)
        X[i] = h
        EFo[i] = abs(target - FiniteDiff.forward.(x, h, f));
        EBa[i] = abs(target - FiniteDiff.backward.(x, h, f));
        ECe[i] = abs(target - FiniteDiff.central.(x, h, f));
    end

    pltErr = plot(X, log10.(EFo), color= :grey, label="Forward", xlabel="x", ylabel="error (log)", title="Error to analytical solution (log), varying h", left_margin=4mm, bottom_margin=3mm)
    plot!(pltErr, X, log10.(EBa), color= :blue, label="Backward")
    plot!(pltErr, X, log10.(ECe), color= :red, label="Central")
end

p = plot(
    plotFunctionAndErrors(-5.0, 5.0, .1, f, f1),
    plotErrorVaryingH(2.5, 100, f, f1),
    layout=grid(1, 2, widths=[0.5, 0.5])
)
plot!(size=(1200, 480))
savefig(p, "f.png")
