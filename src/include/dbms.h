#ifndef DBMS_H

#define DBMS_H
#include <boost/multi_index_container.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/set.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/assume_abstract.hpp>

#include <map>
#include <set>
#include <string>
#include <vector>
#include <sstream>

namespace dbms
{
    class VehicleBase
    {
    protected:
        friend class boost::serialization::access;
        friend class DBMS;
        friend class catalouge;

        std::string m_company;
        std::string m_model;
        enum {
            COLOR,
            ENGINE
        };
        std::vector<std::string> m_others;

        VehicleBase();
        VehicleBase(std::string const & company, std::string const & model , std::vector<std::string> const & others);
        VehicleBase(std::string && company, std::string && model, std::vector<std::string> && others);
        VehicleBase(VehicleBase const &);
        VehicleBase(VehicleBase &&);

        template <class Archive>
        void serialize(Archive &, const unsigned int);

        virtual ~VehicleBase();
    };
    class Vehicle : public VehicleBase
    {
    protected:
        std::string m_product_id;
        friend class boost::serialization::access;

    public:
        Vehicle();
        Vehicle(std::string const & company, std::string const & model, std::vector<std::string> const & others, std::string const & product_id);
        Vehicle(std::string && company, std::string && model, std::vector<std::string> && others, std::string && product_id);
        Vehicle(Vehicle const &);
        Vehicle(Vehicle &&);
        virtual ~Vehicle();

    private:
        template <class Archive>
        void serialize(Archive &ar, const unsigned int version) ;

    };
    class DBMS
    {
        friend class boost::serialization::access;
        std::vector<Vehicle> m_database;

        template <class Archive>
        void serialize(Archive &ar, const unsigned int version) ;

    public:
        DBMS(std::vector<Vehicle> const & vehicle_list);
        ~DBMS();
    };

    //templates 
    template <class Archive>
    void VehicleBase::serialize(Archive & ar , unsigned const int version)
    {
        ar & BOOST_SERIALIZATION_NVP(m_company);
        ar & BOOST_SERIALIZATION_NVP(m_model);
        ar & BOOST_SERIALIZATION_NVP(m_others);
    }

    template <class Archive>
    void Vehicle::serialize(Archive &ar, const unsigned int version) 
    {
        ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(VehicleBase);
        ar & BOOST_SERIALIZATION_NVP(m_product_id);
    }

    template <class Archive>
    void DBMS::serialize(Archive & ar , unsigned const int version)
    {
        ar & BOOST_SERIALIZATION_NVP(m_database);
    }
    
}


#endif