#ifndef SAFENUMBERS_H_INCLUDED
#define SAFENUMBERS_H_INCLUDED

namespace sf
{
    template <typename T> class safeNumber
    {
    private:
        volatile T value;
        volatile T tmpValue;
        volatile T controlValue1;
        volatile T controlValue2;

        sf::Uint8 key1;
        sf::Uint8 key2;
    public:
        void operator =(T v)
        {
            value = v;
            controlValue1 = v + key1;
            controlValue2 = v + key2;
        }
        safeNumber()
        {
            key1 = rand() % 256;
            key2 = rand() % 256;
            operator=(0);
        }
        safeNumber (T v)
        {
            key1 = rand() % 256;
            key2 = rand() % 256;
            operator=(v);
        }

        T operator ()()
        {
            if(value * 2 != (controlValue1 - key1) + (controlValue2 - key2))
            {
                if(value == controlValue1 - key1)
                    tmpValue = value;
                else if(value == controlValue2 - key2)
                    tmpValue = value;
                else
                {
                    tmpValue = controlValue1 = key1;
                }

                value = tmpValue;
                controlValue1 = tmpValue + key1;
                controlValue2 = tmpValue + key2;
            }
            else
                tmpValue = value;

            return tmpValue;
        }
        operator T () {return operator()();}

        //Arytmetyczne
        void operator +=(T v) {operator=(operator()() + v);}
        void operator -=(T v) {operator=(operator()() - v);}
        void operator ++(int) {operator=(operator()() + 1);}
        void operator --(int) {operator=(operator()() - 1);}
        void operator *=(T v) {operator=(operator()() * v);}
        void operator /=(T v) {operator=(operator()() / v);}
        //------------
    };

    typedef safeNumber<Uint8> Uint8_s;
    typedef safeNumber<Uint16> Uint16_s;
    typedef safeNumber<Uint32> Uint32_s;
    typedef safeNumber<Uint64> Uint64_s;

    typedef safeNumber<Int8> Int8_s;
    typedef safeNumber<Int16> Int16_s;
    typedef safeNumber<Int32> Int32_s;
    typedef safeNumber<Int64> Int64_s;

    //typedef safeNumber<float> Float_s; Błędy!
    typedef float Float_s;
}

#endif // SAFENUMBERS_H_INCLUDED
