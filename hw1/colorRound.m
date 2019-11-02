function [M] = colorRound(x,y,colorAround,M)
    M = colorIfNotColored((x-1),(y-1),colorAround,M);
    M = colorIfNotColored((x-1),y,colorAround,M);
    M = colorIfNotColored((x-1),(y+1),colorAround,M);
    M = colorIfNotColored(x,(y-1),colorAround,M);
    M = colorIfNotColored(x,(y+1),colorAround,M);
    M = colorIfNotColored((x+1),(y-1),colorAround,M);
    M = colorIfNotColored((x+1),y,colorAround,M);
    M = colorIfNotColored((x+1),(y+1),colorAround,M);
end

function [M] = colorIfNotColored(x,y,colorAround,M)
    if(M(x,y) == 0)
        M(x,y) = colorAround;
    end
end

