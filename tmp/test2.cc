#define MAPPING(idx, type) \
  field_mapping_db_2_es_.emplace_back(std::make_shared<FieldMapping>()); \
  field_mapping_es_2_db_.emplace_back(std::make_shared<FieldMapping>()); \
  for (const auto& field_info : config->type()) { \
    field_mapping_db_2_es_[idx]->emplace( \
        field_info.db_field(), field_info.es_fields().es_field()); \
    field_mapping_es_2_db_[idx]->emplace( \
        field_info.es_fields().es_field(), field_info.db_field()); \
  }

  MAPPING(0, vid_field_info);
  MAPPING(1, cid_field_info);
  MAPPING(2, col_field_info);
#undef MAPPING
