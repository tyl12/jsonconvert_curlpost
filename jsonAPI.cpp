#include <sstream>
#include <map>
#include <vector>
#include <string>

#include "meta.h"

using namespace std;


#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <iostream>
using namespace rapidjson;

string convertMeta2Json_rj(const Meta_t& meta){
    // document is the root of a json message
    rapidjson::Document doc;

    // define the document as an object rather than an array
    doc.SetObject();

    // create a rapidjson array type with similar syntax to std::vector
    rapidjson::Value array_roi(rapidjson::kArrayType);
    rapidjson::Value array_feature(rapidjson::kArrayType);

    // must pass an allocator when the object may need to allocate memory
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();

    doc.AddMember(Value().SetString("StoreID", allocator),     Value().SetString(meta.StoreID.c_str(), allocator),      allocator);
    doc.AddMember(Value().SetString("Mac", allocator),         Value().SetString(meta.Mac.c_str(), allocator),          allocator);
    doc.AddMember(Value().SetString("UniqueID", allocator),    Value().SetString(meta.UniqueID.c_str(), allocator),     allocator);
    doc.AddMember(Value().SetString("Type", allocator),        Value().SetInt(meta.Type),                               allocator);
    doc.AddMember(Value().SetString("Gender", allocator),      Value().SetInt(meta.Gender),                             allocator);
    doc.AddMember(Value().SetString("Age", allocator),         Value().SetInt(meta.Age),                                allocator);
    doc.AddMember(Value().SetString("TimeStamp", allocator),   Value().SetUint64(meta.TimeStamp),                       allocator);
    doc.AddMember(Value().SetString("CustomerID", allocator),  Value().SetInt(meta.CustomerID),                         allocator);

    for (int i=0;i<4;i++){
        array_roi.PushBack(rapidjson::Value().SetInt(meta.ROI[i]), allocator);
    }
    doc.AddMember("ROI", array_roi, allocator);

    for (int i=0;i<128;i++){
        array_feature.PushBack(rapidjson::Value().SetDouble(meta.Feature[i]), allocator);
    }
    doc.AddMember("Feature", array_feature, allocator);

    rapidjson::StringBuffer strbuf;
    strbuf.Clear();

    rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
    doc.Accept(writer);

    cout<<__FUNCTION__<<" ---->" <<endl;
    cout<<strbuf.GetString()<<endl;

    return strbuf.GetString();
}


#ifdef BOOST_PROP

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;

void example() {
    // Write json.
    ptree pt;
    pt.put ("foo", "bar");
    std::ostringstream buf;
    write_json (buf, pt, false);
    std::string json = buf.str(); // {"foo":"bar"}

    // Read json.
    ptree pt2;
    std::istringstream is (json);
    read_json (is, pt2);
    std::string foo = pt2.get<std::string> ("foo");
}

std::string map2json (const std::map<std::string, std::string>& map) {
    ptree pt;
    for (auto& entry: map)
        pt.put (entry.first, entry.second);
    std::ostringstream buf;
    write_json (buf, pt, false);
    return buf.str();
}

string convertMeta2Json_boost(const Meta_t& meta){
    ptree root;
    root.put("StoreID",     meta.StoreID);
    root.put("Mac",         meta.Mac);
    root.put("UniqueID",    meta.UniqueID);
    root.put("Type",        meta.Type);
    root.put("Gender",      meta.Gender);
    root.put("Age",         meta.Age);
    root.put("TimeStamp",   meta.TimeStamp);
    root.put("CustomerID",  meta.CustomerID);
    ptree rois;
    for (int i=0;i<4;i++){
        ptree node;
        node.put("",meta.ROI[i]);
        rois.push_back(std::make_pair("", node));
    }
    root.add_child("ROI",         rois);

    ptree features;
    for (int i=0;i<128;i++){
        ptree node;
        node.put("",meta.Feature[i]);
        features.push_back(std::make_pair("", node));
    }
    root.add_child("Feature",    features);

    std::ostringstream buf;
    write_json(buf, root, false);
    string json = buf.str();

    //print to screen
    cout<<__FUNCTION__<<" ---->" <<endl;
    write_json(std::cout, root);

    return json;
}
#endif


#ifdef DEBUG
int main(){

    string result;
    Meta_t meta;
#ifdef BOOST_PROP
    result = convertMeta2Json_boost(meta);
    cout<<result<<endl;
#endif

    result = convertMeta2Json_rj(meta);

    return 0;
}
#endif
