#ifndef MATH_H_INCLUDED
#define MATH_H_INCLUDED

float aToRadian(float f)
{
    return f * PI/180;
}

float atan2f(const float x, const float y)
{
    float r;

    if ((x == 0.0f) && (y == 0.0f))
        return 0.0;

    if(fabsf(y)>=fabsf(x))
    {
        r = atanf(x / y);
        if(y < 0.0)
            r += (x >= 0 ? PI : -PI);
    }
    else
    {
        r = -atanf(y / x);
        r += (x < 0.0f ? -HALF_PI : HALF_PI);
    }
    return r;
}

float rotate_to_ff(const sf::Vector2f& point1, const sf::Vector2f& point2)
{
    float dx = point2.x - point1.x;
    float dy = point2.y - point1.y;

    float radian = atan2f(dy, dx);
    return (radian * 180 / PI);
}

float rotate_to_fi(const sf::Vector2f& point1, const sf::Vector2i& point2)
{
    float dx = point2.x - point1.x;
    float dy = point2.y - point1.y;

    float radian = atan2f(dy, dx);
    return (radian * 180 / PI);
}

double ctg(double d)
{
    return (1 / tan(d));
}

float Map(float x, float in_min, float in_max, float out_min, float out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

sf::Vector2f onCircle(sf::Vector2f theta, float radiaus, float angle)
{
    sf::Vector2f tmp;

    tmp.x = cos(aToRadian(angle)) * radiaus + theta.x;
    tmp.y = sin(aToRadian(angle)) * radiaus + theta.y;

    return tmp;
}

float limit(float value, float _from, float _to)
{
    if(value < _from)
        value = _from;
    else if(value > _to)
        value = _to;

    return value;
}
#endif // MATH_H_INCLUDED
