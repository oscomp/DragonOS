use another_ext4::Ext4Error;


impl From<Ext4Error> for super::SystemError {
    fn from(err: Ext4Error) -> Self {
        log::error!("Ext4Error: {:?}", err);
        <Self as num_traits::FromPrimitive>::from_i32(err.code() as i32).unwrap()
    }
}
