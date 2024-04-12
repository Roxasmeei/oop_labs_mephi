#include <gtest/gtest.h>
#include <Descriptors.h>





TEST(MasterDescriptorTest, ConstructorWithValidContribution) {
    MasterDescriptor master(3.5);
    ASSERT_EQ(master.GetContribution(), 3.5);
}

TEST(MasterDescriptorTest, ConstructorWithInvalidContribution) {
    ASSERT_THROW(MasterDescriptor(-1), std::invalid_argument);
    ASSERT_THROW(MasterDescriptor(6), std::invalid_argument);
}

TEST(MasterDescriptorTest, SetContributionWithValidValue) {
    MasterDescriptor master;
    master.SetContribution(2.0);
    ASSERT_EQ(master.GetContribution(), 2.0);
}

TEST(MasterDescriptorTest, SetContributionWithInvalidValue) {
    MasterDescriptor master;
    ASSERT_THROW(master.SetContribution(-1), std::invalid_argument);
    ASSERT_THROW(master.SetContribution(6), std::invalid_argument);
}

TEST(StandardWorkerDescriptorTest, ConstructorWithValidContribution) {
    StandardWorkerDescriptor worker(8);
    ASSERT_EQ(worker.GetContribution(), 8.0);
}

TEST(StandardWorkerDescriptorTest, ConstructorWithInvalidContribution) {
    ASSERT_THROW(StandardWorkerDescriptor(0.0), std::invalid_argument);
    ASSERT_THROW(StandardWorkerDescriptor(11), std::invalid_argument);
}

TEST(StandardWorkerDescriptorTest, SetContributionWithValidValue) {
    StandardWorkerDescriptor worker;
    worker.SetContribution(5.0);
    ASSERT_EQ(worker.GetContribution(), 5.0);
}

TEST(StandardWorkerDescriptorTest, SetContributionWithInvalidValue) {
    StandardWorkerDescriptor worker;
    ASSERT_THROW(worker.SetContribution(0), std::invalid_argument);
    ASSERT_THROW(worker.SetContribution(11), std::invalid_argument);
}

TEST(DescriptorConversionTest, StandardWorkerToMasterConversionWithStadardWorkerContributionNotMin) {
    StandardWorkerDescriptor standard1(4.0);
    MasterDescriptor master1(&standard1);
    ASSERT_EQ(master1.GetContribution(), standard1.GetContribution() / 2);
}

TEST(DescriptorConversionTest, StandardWorkerToMasterConversionWithStadardWorkerContributionMin) {
    StandardWorkerDescriptor standard1(1.0);
    MasterDescriptor master1(&standard1);
    ASSERT_EQ(master1.GetContribution(), standard1.GetContribution());
}

TEST(DescriptorConversionTest, MasterToStandardWorkerConversionWithMasterContributionNotMin) {
    MasterDescriptor master1(4.5);
    StandardWorkerDescriptor worker1(&master1);
    ASSERT_EQ(master1.GetContribution(), (double)worker1.GetContribution() / 2);
}

TEST(DescriptorConversionTest, MasterToStandardWorkerConversionWithMasterContributionMin) {
    MasterDescriptor master1(1.0);
    StandardWorkerDescriptor worker1(&master1);
    ASSERT_EQ(master1.GetContribution(), (double)worker1.GetContribution());
}

TEST(DescriptorConversionTest, StandardWorkerToStandardWorkerConversion) {
    StandardWorkerDescriptor standard1(4.0);
    StandardWorkerDescriptor standard2(&standard1);
    ASSERT_EQ(standard1.GetContribution(), standard2.GetContribution());
}


TEST(DescriptorConversionTest, MasterToMasterConversion) {
    MasterDescriptor master1(4.5);
    MasterDescriptor master2(&master1);
    ASSERT_EQ(master1.GetContribution(), master2.GetContribution());
}