## imsdk的数据流程

object -> json string -> json object -> pb packet

```
makeMessagePacket(int seq, const std::string &json_str)
{
    jsonxx::Object json;
    if (!json.parse(json_str)) {
        LOG_E("LibWarthogJNI", "parse json failed: %s", json_str.c_str());
        return nullptr;
    }

    PBPacket::uptr pb_packet = PBPacket::MakeUniquePtr(seq);
    PBPacket::Packv2 &pb_pack = pb_packet->GetPBPackv2();
    pb_pack.set_pack_type(::im::v2::IM_PACK);

    ::im::v2::PBIMPackV2 *pb_im_pack = pb_pack.mutable_im_pack();
    pb_im_pack->set_type(::im::v2::PBIMPackV2::SEND_MESSAGE);

    ::im::v2::PBIMSendMessage *pb_send_msg = pb_im_pack->mutable_send_msg();
    FillIMClientInfo(seq, pb_send_msg->mutable_client_info());

    if (json.has<jsonxx::Integer>("msg_type"))
    {
        pb_send_msg->set_msg_type((int32_t) json.get<jsonxx::Integer>("msg_type"));
    }
    if (json.has<jsonxx::Integer>("sender_id"))
    {
        pb_send_msg->set_sender_id(json.get<jsonxx::Integer>("sender_id"));
    }
    if (json.has<jsonxx::Integer>("target_type"))
    {
        pb_send_msg->set_target_type((int32_t) json.get<jsonxx::Integer>("target_type"));
    }
    if (json.has<jsonxx::Integer>("target_id"))
    {
        pb_send_msg->set_target_id(json.get<jsonxx::Integer>("target_id"));
    }
    if (json.has<jsonxx::Integer>("content_type"))
    {
        pb_send_msg->set_content_type((int32_t) json.get<jsonxx::Integer>("content_type"));
    }
    if (json.has<jsonxx::String>("content"))
    {
        pb_send_msg->set_content(json.get<jsonxx::String>("content"));
    }
    
    if (json.has<jsonxx::Integer>("timestamp"))
    {
        pb_send_msg->set_timestamp(json.get<jsonxx::Integer>("timestamp"));
    }
    if (json.has<jsonxx::Integer>("from"))
    {
        pb_send_msg->set_from((int32_t) json.get<jsonxx::Integer>("from"));
    }

    return pb_packet;
}
```

## 对于pb的结构


```
头文件里，除了一堆辅助方法，有私有成员变量，对应proto

::std::string _unknown_fields_;

::google::protobuf::uint32 _has_bits_[1];
mutable int _cached_size_;
::google::protobuf::int32 msg_type_;
::google::protobuf::int64 sender_id_;
::google::protobuf::int64 target_id_;
::google::protobuf::int32 content_type_;
::std::string* content_;
::google::protobuf::int64 timestamp_;
::google::protobuf::int32 from_;

```

但是pb的使用方法，只能调用起setter....那么就需要 分析proto，产出转化实现？