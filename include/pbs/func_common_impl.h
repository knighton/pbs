namespace pbs {

void SequenceReadResult::Clear() {
    num_ok = 0;
    num_bad_checksum = 0;
    num_bad_proto = 0;
}

}  // namespace pbs
