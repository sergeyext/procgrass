function bezier4()
    figure;
    hold on;
    axis([-10 10 -10 10]);
    [x,y] = ginput(4);
    scatter(x,y, 'b');
    
    p0x = x(1);p1x = x(2);p2x = x(3);p3x = x(4);
    p0y = y(1);p1y = y(2);p2y = y(3);p3y = y(4);
    
    syms t;
    x1_sym = p3x*t^3 - p0x*(t - 1)^3 + 3*p1x*t*(t - 1)^2 - 3*p2x*t^2*(t - 1);
    y1_sym = p3y*t^3 - p0y*(t - 1)^3 + 3*p1y*t*(t - 1)^2 - 3*p2y*t^2*(t - 1);
    t_beg = 0;
    t_step = 0.02;
    t_end = 1;
    t_num = (t_end - t_beg) / t_step;
    xs = zeros(1, t_num);
    ys = zeros(1, t_num);
    for idx = 1:t_num;
        i = idx * t_step;
        x1 = subs(x1_sym, t, i);
        y1 = subs(y1_sym, t, i);
        xs(idx) = x1;
        ys(idx) = y1;
    end
    scatter(xs, ys, 'r');
    axis([-10 10 -10 10]);

end
