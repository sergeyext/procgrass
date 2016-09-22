function [ output_args ] = bisect( input_args )

    x = [0, 1, 8];
    y = [0, 1, 4];
    z = [0, 0, 0];
    
    B = [x(2), y(2)];
    BA = [x(1) - x(2), y(1) - y(2)];
    BC = [x(3) - x(2), y(3) - y(2)];
    ABC = acos(dot(BA, BC)/(norm(BA) * norm(BC)));
    toDegrees('radians', ABC)
    phi = -(pi/2 - ABC/2);
    rotm = [[cos(phi), -sin(phi)]; [sin(phi), cos(phi)]];
    
    nBA = BA/norm(BA);
    nBC = BC/norm(BC);
    
    bisect = nBA + nBC;
    ort_bisect = rotm * nBA';
    
    figure;
    hold on;
    axis equal;
    
    plot(x,y, [B(1), B(1)+bisect(1)], [B(2), B(2)+bisect(2)], [B(1), B(1)+ort_bisect(1)], [B(2), B(2)+ort_bisect(2)]);
    plot([B(1), B(2)], [3,3]);    
end

