use alloc::sync::Arc;

impl crate::filesystem::vfs::FileSystemMakerData for Arc<super::GenDisk> {
    fn as_any(&self) -> &dyn core::any::Any {
        self
    }
}